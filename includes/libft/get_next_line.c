/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsaldana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 13:04:16 by bsaldana          #+#    #+#             */
/*   Updated: 2025/06/04 13:52:52 by bsaldana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc((strlen_gnl(s1) + strlen_gnl(s2) + 2) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0' && s2[j] != '\n')
	{
		str[i + j] = s2[j];
		j++;
	}
	if (s2[j] == '\n')
		str[i + j++] = '\n';
	str[i + j] = '\0';
	return (free(s1), str);
}

static int	ft_strchr_gnl(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return ((int)0);
}

static char	*ft_copytext(char *buffer, int fd, char **aux, char **end_line)
{
	int		check;
	char	*temp;

	check = read(fd, buffer, BUFFER_SIZE);
	if (check == -1)
		return (free(*aux), NULL);
	while (check > 0)
	{
		buffer[check] = '\0';
		temp = ft_strjoin_gnl(*aux, buffer);
		if (!temp)
			return (free(*aux), NULL);
		*aux = temp;
		if (ft_strchr_gnl(buffer, '\n'))
		{
			if (*end_line)
				free(*end_line);
			*end_line = ft_divide_gnl(buffer);
			return (*aux);
		}
		check = read(fd, buffer, BUFFER_SIZE);
	}
	if (*aux && **aux)
		return (*aux);
	return (free(*aux), NULL);
}

static char	*check_end_line(char **aux, char **end_line)
{
	char	*temp;

	temp = *end_line;
	*aux = ft_strjoin_gnl(*aux, *end_line);
	if (!*aux)
		return (NULL);
	*end_line = ft_divide_gnl(temp);
	free(temp);
	return (*aux);
}

char	*get_next_line(int fd)
{
	static char	*end_line = NULL;
	char		*buffer;
	char		*aux;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	aux = ft_strdup_gnl("");
	if (end_line)
	{
		if (ft_strchr_gnl(end_line, '\n'))
		{
			line = check_end_line(&aux, &end_line);
			return (free(buffer), line);
		}
		aux = ft_strjoin_gnl(aux, end_line);
		free(end_line);
		end_line = NULL;
	}
	line = ft_copytext(buffer, fd, &aux, &end_line);
	return (free(buffer), line);
}
