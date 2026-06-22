/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsaldana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:43:43 by bsaldana          #+#    #+#             */
/*   Updated: 2025/05/27 15:52:11 by bsaldana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	strlen_gnl(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_divide_gnl(char *buffer)
{
	int		i;
	int		j;
	int		size;
	char	*end_line;

	i = 0;
	j = 0;
	size = strlen_gnl(buffer);
	while ((buffer[i] && buffer[i] != '\n'))
		i++;
	i++;
	end_line = (char *)malloc(sizeof(char) * (size - i + 1));
	if (!end_line)
		return (NULL);
	while (buffer[i + j] != '\0')
	{
		end_line[j] = buffer[i + j];
		j++;
	}
	end_line[j] = '\0';
	return (end_line);
}

char	*ft_strdup_gnl(char *s)
{
	int		l;
	int		i;
	char	*dup;

	l = strlen_gnl(s);
	i = 0;
	dup = (char *)malloc((l + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	while (s[i] != '\0')
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
