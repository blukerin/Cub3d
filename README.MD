> (EL ARCHIVO map2D.c CONTIENE TODAS LAS FUCIONES DE LA FASE DE PRUEBA EN LA QUE HACIA LOS RAYITOS EN 2D)

he formateado el readme con cursor para que sea más leible xd.

# Cub3D — Notas del proyecto

## El flujo del programa

```
map.cub → parser → init_player → init_game → render → bucle MLX (teclas)
```

En `main.c`:

1. Reservar memoria para textures y map
2. Parsear el .cub
3. Inicializar al jugador
4. Abrir la ventana con MiniLibX
5. Renderizar (hoy vacío)
6. Escuchar teclas y quedarse en el bucle

---

## Estructuras de datos (`cub3D.h`)

Cuatro piezas principales:

| Estructura   | Qué guarda                                              |
|--------------|---------------------------------------------------------|
| `t_map`      | Grid del mapa ('0' suelo, '1' pared) + tamaño           |
| `t_player`   | Posición, dirección de mirada y plano de cámara         |
| `t_textures` | Rutas de texturas + colores suelo/techo                 |
| `t_game`     | MLX, ventana, mapa, texturas y jugador                  |

Constantes útiles ya definidas: teclas (W/A/S/D, flechas, ESC), FOV, velocidades de movimiento y rotación.

---

## Inicialización del jugador (`init_player.c`)

Tras el parser, el jugador ya tiene posición en celdas y orientación (N/S/E/W). Aquí se convierte a coordenadas 3D:

- **Centra al jugador en la casilla:** `(x, y) → (x + 0.5, y + 0.5)`: cada casilla es un numero entero, pero para tener mas precision dentro de las celdas usamos decimales (por eso el centro de la casilla es la posicion de la casilla en el eje x + 0.5 y y + 0.5). Este enfoque nos servira para calcular despues el punto exacto donde pegan los rayos en las casillas.

- **Calcula el vector dirección según la orientación:**
  - para ello calculamos la orientacion en el eje x:
    - E → mira a la derecha (1, 0)
    - W → mira a la izquierda (-1, 0)
  - y en el eje y:
    - N → mira arriba (0, -1) (la y crece hacia abajo porque el mapa se printea de arriba a abajo, por eso es negativa)
    - S → mira abajo (0, 1)
    - etc.

- **Calcula el plano de cámara** (`cam_plane_x/y`) con factor 0.66 — típico para raycasting (campo de visión ~66°): calculamos el vector perpendicular (para ellos invertimos las restas, en vez de `(d == 'S') - (d == 'N')` hacemos `(d == 'N') - (d == 'S')`) y lo multiplicamos por 0.66 para que sea un 66% del vector de la direccion del personaje, si fuera igual de largo tendriamos un angulo de vision de 90 grados, lo cual se ve poco natural.

- Sustituye N/S/E/W en el mapa por `'0'` para que el personaje no choque consigo mismo.

> Para tener una representacion visual de los vectores: orientacion del jugador y plano de la camara (perpendicular a este) ver [lodev.org/cgtutor/raycasting.html](https://lodev.org/cgtutor/raycasting.html) en la seccion THE BASIC IDEA

---

## Inicialización del juego (`init_game.c`)

- `mlx_init()` — arranca MiniLibX
- Ventana de tamaño mapa × 100 píxeles por celda (pensado para vista 2D)
- Título: `"cub3D"`

> **TODO:** TENDRIAMOS QUE REPENSAR LA RESOLUCION Y EL TAMAÑO DE LAS CELDAS, SEGURAMENTE TENGAMOS QUE TOCAR ESTA FUNCION

---

## Movimiento del jugador (`player.c`)

Esta funcion es un troncho tremendo, tocará refactorizar fuerte. La idea es que antes de cambiar cada x e y compruebe que no se esta saliendo del mapa, mirando que el valor que vamos a poner siempre caiga en una casilla que es '0'. Nos movemos en cada direccion MOVE_SPEED que es un 5% de la casilla en la direccion a la que nos movamos.

Cada pulsación mueve al jugador un poco. La posición son coordenadas decimales `(pos_x, pos_y)` y la dirección de mirada es el vector `(dir_x, dir_y)`.

### W / S — adelante / atrás

- W suma dir_x y dir_y × MOVE_SPEED (vamos hacia donde miramos).
- S hace lo mismo pero multiplicando por -1 (vamos hacia atrás).
- No confundir W con "arriba del mapa": si miramos al Este, W solo mueve en X.

### A / D — strafe (desplazamiento lateral)

Son perpendiculares a la dirección de mirada:

- **D (derecha):** `pos_x += dir_y × 0.05` y `pos_y -= dir_x × 0.05`
- **A (izquierda):** `pos_x -= dir_y × 0.05` y `pos_y += dir_x × 0.05`

---

## Rotación del jugador (`rotate_player` en `player.c`)

Las flechas ← y → giran la cámara sin mover la posición del jugador.

- `ROT_SPEED = 0.03` radianes por pulsación (~1.7°).
- Flecha izquierda: rot negativo. Flecha derecha: rot positivo.

Hay que rotar dos vectores a la vez:

- `(dir_x, dir_y)` → hacia dónde miramos
- `(cam_plane_x, cam_plane_y)` → ancho del campo de visión (perpendicular a dir)

Se usa la fórmula de rotación 2D:

```
nuevo_x = x · cos(rot) - y · sin(rot)
nuevo_y = x · sin(rot) + y · cos(rot)
```

Primero se rota dir, luego cam_plane con la misma fórmula y el mismo ángulo.
Guardamos el x antiguo en una variable temp porque hace falta para calcular el nuevo y.

Si solo rotáramos dir y no cam_plane, el raycasting se vería mal.

---

## Hooks / eventos (`hooks.c`)

- ESC o cerrar ventana → libera memoria y cierra MLX
- Cualquier tecla de movimiento → mueve/rota y llama a `render()`

---

## Render — algoritmo DDA (Digital Differential Analyzer)

A CONTINUACION NOS TOCA EL NUCLEO DEL PROYECTO EN RENDER(): EL ALGORITMO DDA (Digital Differential Analyzer)

Para que te hagas una idea visual ver https://lodev.org/cgtutor/raycasting.html en la sección UNTEXTURED RAYCASTER

la pantalla tiene WIN_W = 1024 columnas de píxeles. Por cada columna vertical de la pantalla vamos a lanzar un rayo desde el jugador hacia el mapa. Ese rayo avanza hasta que choca con una pared. Según lo lejos que esté esa pared, dibujamos esa columna de pared más alta (cerca) o más baja (lejos).

El bucle central es que, para cada columna x de 0 a 1023:

1. calcular la dirección del rayo de esa columna
2. avanzar el rayo por el mapa hasta chocar con una pared  ← ESTO ES EL DDA
3. medir la distancia a la pared
4. dibujar una raya vertical de altura proporcional a esa distancia

### Paso 1 del bucle: la dirección de cada rayo

La IA recomienda empezar asi:

> "Paso 1 del bucle: la dirección de cada rayo
> Recorremos las columnas de pantalla x de 0 a WIN_W - 1 (0 a 1023).
>
> Necesitamos convertir "columna número x" en "un número que va de -1 (borde izquierdo) a +1 (borde derecho)". Ese número se llama camera_x:
>
> ```c
> double camera_x = 2.0 * x / (double)WIN_W - 1.0;
> ```
>
> Comprobemos que funciona:
>
> Si x = 0 (primera columna) → camera_x = 0 - 1 = -1 → borde izquierdo.
> Si x = 512 (columna del medio) → camera_x ≈ 0 → centro, justo donde miras.
> Si x = 1023 (última) → camera_x ≈ +1 → borde derecho.
> Ahora construimos el rayo de esa columna combinando dir con cam_plane según camera_x:
>
> ```c
> double ray_dir_x = player.dir_x + player.cam_plane_x * camera_x;
> double ray_dir_y = player.dir_y + player.cam_plane_y * camera_x;
> ```
>
> Columna del medio (camera_x = 0): el rayo es exactamente dir (miras al frente).
> Columna izquierda (camera_x = -1): el rayo es dir - cam_plane (borde izquierdo del abanico).
> Columna derecha (camera_x = +1): el rayo es dir + cam_plane (borde derecho).
> Ya tenemos la flecha (ray_dir_x, ray_dir_y) que apunta desde el jugador hacia donde debe ir ESE rayo. Ahora empieza el DDA de verdad: hacer que esa flecha "camine" por el mapa hasta chocar."

El rayo sale del jugador y avanza en línea recta. en algun momento cruzará líneas de la cuadrícula: las líneas verticales (que separan columnas de casillas) y las líneas horizontales (que separan filas de casillas). En vez de avanzar pasito a pasito, saltamos directamente de línea de cuadrícula a línea de cuadrícula. Porque una pared solo puede empezar en el borde de una casilla. Entonces solo necesitamos comprobar los puntos donde el rayo cruza esas líneas.

La IA dice: "La pregunta clave en cada paso es:

¿Qué está más cerca: la siguiente línea vertical o la siguiente línea horizontal?

Saltamos a la que esté más cerca, comprobamos en qué casilla hemos entrado, y si es 1 → paren todo, choque. Si no, repetimos.

Es como cruzar un campo de baldosas: en lugar de mirar cada milímetro, solo miras cuando pisas una raya nueva del suelo."

### Variables del DDA

Las variables que necesitamos:

> " map_x, map_y — en qué casilla estás
> Simplemente la parte entera de tu posición. Si estás en pos_x = 2.5, estás en la columna map_x = 2.
>
> ```c
> int map_x = (int)player.pos_x;
> int map_y = (int)player.pos_y;
> ```
>
> Estos irán cambiando: cada vez que el rayo cruza una línea, sumamos o restamos 1 a map_x o a map_y.
>
> step_x, step_y — hacia qué lado avanzamos
> El rayo puede ir hacia la derecha o hacia la izquierda (en X), y hacia abajo o hacia arriba (en Y). step dice si sumamos +1 o -1 a la casilla:
>
> ```c
> int step_x = (ray_dir_x < 0) ? -1 : 1;
> int step_y = (ray_dir_y < 0) ? -1 : 1;
> ```
>
> Si el rayo apunta a la derecha (ray_dir_x positivo) → avanzaremos de casilla en casilla hacia la derecha (+1).
> Si apunta a la izquierda → -1.
>
> delta_dist_x, delta_dist_y — el precio de cruzar una casilla entera
> Esta es la parte que asusta pero es sencilla con un dibujo.
>
> delta_dist_x = cuánta distancia recorre el rayo (a lo largo del propio rayo) para avanzar exactamente 1 casilla en la dirección X.
>
> delta_dist_y = lo mismo pero para avanzar 1 casilla en la dirección Y.
>
> Piensa en una escalera. Si vas muy "de frente" en X (rayo casi horizontal), cruzar una columna cuesta poco. Si vas casi vertical, cruzar una columna en X te cuesta muchísimo recorrido de rayo (porque apenas te mueves en X).
>
> La fórmula estándar y segura es:
>
> ```c
> double delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1.0 / ray_dir_x);
> double delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1.0 / ray_dir_y);
> ```
>
> Interpretación intuitiva del 1/ray_dir_x:
>
> Si el rayo se mueve mucho en X (ray_dir_x grande) → 1/ray_dir_x es pequeño → cruzar una columna cuesta poco recorrido. Lógico.
> Si el rayo se mueve poco en X (ray_dir_x casi 0) → 1/ray_dir_x es enorme → cruzar una columna cuesta un montón. Lógico.
> El 1e30 (número gigante) es para evitar dividir por cero cuando el rayo es perfectamente horizontal o vertical: significa "esa dirección nunca cruzará esa línea, cuesta infinito".
> No necesitas entender la demostración matemática. Quédate con: delta_dist = "cuánto rayo gasto para saltar una casilla en ese eje".
>
> side_dist_x, side_dist_y — cuánto falta para la PRIMERA línea
> delta_dist es el coste de cruzar una casilla entera. Pero al principio tú no estás pegado a una línea, estás en medio de una casilla (ej: pos_x = 2.5). Así que el primer salto es más corto: solo hasta la primera línea de cuadrícula.
>
> side_dist_x = distancia de rayo desde tu posición hasta la primera línea vertical. side_dist_y = distancia de rayo desde tu posición hasta la primera línea horizontal.
>
> Depende de hacia dónde vayas:
>
> ```c
> if (ray_dir_x < 0)
>     side_dist_x = (player.pos_x - map_x) * delta_dist_x;
> else
>     side_dist_x = (map_x + 1.0 - player.pos_x) * delta_dist_x;
> if (ray_dir_y < 0)
>     side_dist_y = (player.pos_y - map_y) * delta_dist_y;
> else
>     side_dist_y = (map_y + 1.0 - player.pos_y) * delta_dist_y;
> ```
>
> Ejemplo: estás en pos_x = 2.5, map_x = 2.
>
> Si el rayo va a la derecha, la siguiente línea vertical está en x = 3. Te falta 3 - 2.5 = 0.5 de casilla. Multiplicado por delta_dist_x da la distancia real de rayo.
> Si va a la izquierda, la siguiente línea está en x = 2. Te falta 2.5 - 2 = 0.5."

PARA VER REPRESENTADO ESTO YA TE DIGO QUE PUEDES MIRAR EN LA SECCION -> UNTEXTURED RAYCASTER

### El bucle del DDA (el corazón)

> "El bucle del DDA (el corazón)
> Ya tenemos todo preparado. Ahora el rayo camina:
>
> ```c
> int hit = 0;
> int side;   // ¿chocamos en una línea vertical (0) o horizontal (1)? lo usaremos luego
> while (hit == 0)
> {
>     if (side_dist_x < side_dist_y)   // la línea vertical está más cerca
>     {
>         side_dist_x += delta_dist_x; // avanzamos el rayo hasta esa línea
>         map_x += step_x;             // entramos en la casilla de al lado (en X)
>         side = 0;                    // chocamos por un lado vertical (E/W)
>     }
>     else                              // la línea horizontal está más cerca
>     {
>         side_dist_y += delta_dist_y;
>         map_y += step_y;
>         side = 1;                    // chocamos por un lado horizontal (N/S)
>     }
>     if (map->grid[map_y][map_x] == '1')  // ¿la casilla nueva es pared?
>         hit = 1;                          // ¡choque! salimos
> }
> ```
>
> Léelo como una historia:
>
> ¿Qué línea está más cerca, la vertical o la horizontal? Comparamos side_dist_x vs side_dist_y.
> Saltamos a la más cercana: le sumamos su delta_dist (para que la próxima vez apunte a la siguiente línea de ese tipo) y cambiamos de casilla con step.
> Miramos la casilla nueva en tu grid. Si es '1', hemos chocado con una pared y salimos. Si es '0', el while repite.
> side guarda si el último salto fue vertical u horizontal. Nos hará falta ahora mismo para dos cosas: medir bien la distancia y (más adelante) saber qué textura N/S/E/W usar.
>
> Es literalmente un bucle que va comiendo casillas en línea recta hasta topar con un muro. Nada más.
>
> Medir la distancia (y por qué "perpendicular")
> Cuando salimos del bucle, sabemos en qué casilla 1 chocamos. Ahora: ¿a qué distancia está esa pared? Porque de eso depende la altura de la raya que pintamos.
>
> Aquí hay una trampa importante. Si midiéramos la distancia real (en línea recta) del jugador a la pared, aparecería un efecto de "ojo de pez" (fish-eye): las paredes rectas se verían curvadas, abombadas en el centro. Eso pasa porque los rayos de los bordes recorren más distancia que los del centro aunque la pared esté igual de lejos.
>
> La solución: en vez de la distancia real, usamos la distancia perpendicular al plano de cámara. Y hay un truco muy limpio: como ya fuimos acumulando side_dist, esa distancia perpendicular es simplemente el último side_dist menos su delta_dist (le quitamos el último salto que nos "pasó" al otro lado):
>
> ```c
> double perp_wall_dist;
> if (side == 0)
>     perp_wall_dist = (side_dist_x - delta_dist_x);
> else
>     perp_wall_dist = (side_dist_y - delta_dist_y);
> ```
>
> No hace falta calcular raíces cuadradas ni distancias reales. Este método ya da directamente la distancia perpendicular correcta y elimina el ojo de pez.
>
> Dibujar la columna de pared
> Ya tenemos perp_wall_dist. Convertimos distancia en altura de la raya en pantalla:
>
> ```c
> int line_height = (int)(WIN_H / perp_wall_dist);
> ```
>
> Pared cerca → perp_wall_dist pequeño → line_height grande → raya alta.
> Pared lejos → distancia grande → raya baja. Justo el efecto de profundidad que queremos.
> Ahora, ¿dónde empieza y acaba esa raya vertical? La centramos en la pantalla:
>
> ```c
> int draw_start = -line_height / 2 + WIN_H / 2;
> if (draw_start < 0)
>     draw_start = 0;
> int draw_end = line_height / 2 + WIN_H / 2;
> if (draw_end >= WIN_H)
>     draw_end = WIN_H - 1;
> ```
>
> WIN_H / 2 es el centro vertical de la pantalla (el horizonte).
> Ponemos media pared por encima y media por debajo del horizonte.
> Los if recortan por si la pared es tan alta que se sale de la pantalla (cuando estás pegadísimo a ella).
> Y por fin dibujamos, para esta columna x, tres tramos con tu pixel_put_image:
>
> ```c
> // del techo (0) a draw_start → color de techo
> // de draw_start a draw_end   → la pared
> // de draw_end al fondo (WIN_H) → color de suelo
> ```
>
> En una versión sin texturas (que es por donde deberías empezar), la pared es un color plano. Puedes usar side para pintar los lados horizontales un poco más oscuros que los verticales, y así se distinguen las esquinas (da sensación de sombra/relieve)."

------
