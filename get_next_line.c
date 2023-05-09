/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:50:05 by jihalee           #+#    #+#             */
/*   Updated: 2023/05/09 18:01:11 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*result;
	size_t	total;

	total = size * nmemb;
	if (size != 0 && nmemb != 0 && (total < nmemb || total < size))
		return (NULL);
	result = (void *)malloc(total);
	if (result == 0)
		return (0);
	ft_bzero(result, total);
	return (result);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	size_t	i;
	char	*new_string;

	len = 0;
	while (s[len])
		len++;
	new_string = (char *)malloc(sizeof (char) * (len + 1));
	if (new_string == 0)
		return (0);
	i = 0;
	while (i < len)
	{
		new_string[i] = s[i];
		i++;
	}
	new_string[i] = '\0';
	return (new_string);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	ch;

	ch = c;
	i = 0;
	while (s[i])
	{
		if (s[i] == ch)
			return (&((char *)s)[i]);
		i++;
	}
	if (c == '\0')
		return (&(((char *)s)[i]));
	return (0);
}

int	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (start >= ft_strlen(s))
	{
		sub = (char *)malloc(sizeof (char) * 1);
		if (sub != 0)
			sub[0] = '\0';
		return (sub);
	}
	else if (len > ft_strlen(s + start))
		sub = (char *)malloc(sizeof (char) * (ft_strlen(s + start) + 1));
	else
		sub = (char *)malloc(sizeof (char) * (len + 1));
	if (sub == 0)
		return (NULL);
	i = 0;
	while (i < len && s[start + i] && start < ft_strlen(s))
	{
		sub[i] = s[(size_t)start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*append(char *s1, char const *s2)
{
	int		i;
	int		j;
	int		len;
	char	*result;

	len = ft_strlen(s1) + ft_strlen(s2);
	result = (char *)malloc(sizeof (char) *(len + 1));
	if (result == 0)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	free (s1);
	return (result);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*str;
	char		*result;
	int			bytes_read;

	buf = (char *)calloc(BUFFER_SIZE + 1, sizeof (char));
	if (buf == 0)
		return (NULL);
	if (str == 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == 0 || bytes_read == -1)
		{
			free(buf);
			return (NULL);
		}
		str = (char *)calloc(1, 1);
		str = append(str, buf);
	}
	while (strchr(str, '\n') && bytes_read)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		str = append(str, buf);
	}
	if (bytes_read == 0)
	{
		
	}
	return (NULL);
}

#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int	main()
{
	int	fd;
	char buf[100];
	int	r_read;

	memset(buf, 'a', 100);
	fd = open("testfile", O_RDWR);
	r_read = read(fd, buf, BUFFER_SIZE);
	printf ("r_read :%d, the string %s\n", r_read, buf);
	r_read = read(fd, buf, BUFFER_SIZE);
	printf ("r_read :%d, the string %s\n", r_read, buf);
	return (0);
}
