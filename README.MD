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


A CONTINUACION NOS TOCA EL NUCLEO DEL PROYECTO EN RENDER(): EL ALGORITMO DDA (Digital Differential Analyzer)

Para que te hagas una idea visual ver https://lodev.org/cgtutor/raycasting.html en la sección UNTEXTURED RAYCASTER



