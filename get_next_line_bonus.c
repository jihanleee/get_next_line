/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:50:05 by jihalee           #+#    #+#             */
/*   Updated: 2023/05/11 21:16:52 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	add_to_list(char *buf, t_list **list)
{
	int		i;
	int		j;
	int		eol_found;

	eol_found = 0;
	j = 0;
	while (buf[j])
	{
		i = j;
		while (buf[i] && buf[i] != '\n')
			i++;
		if (buf[i] == '\n')
		{
			eol_found = 1;
			i++;
		}
		if (*list == 0)
			*list = ft_lstnew(ft_substr(buf, j, i - j), i - j);
		else
			ft_lstadd_back(list, ft_lstnew(ft_substr(buf, j, i - j), i - j));
		j = i;
	}
	return (eol_found);
}

int	make_list(int fd, t_list **list)
{
	char	*buf;
	int		size_read;

	buf = (char *)malloc(sizeof (char) * (BUFFER_SIZE + 1));
	if (buf == 0)
		return (0);
	while (1)
	{
		size_read = read(fd, buf, BUFFER_SIZE);
		if (size_read <= 0)
			break ;
		buf[size_read] = '\0';
		if (add_to_list(buf, list) == 1)
			break ;
	}
	free(buf);
	if (size_read == -1)
		return (0);
	return (1);
}

int	get_size(t_list *list)
{
	int		size;

	size = 0;
	while (list)
	{
		size += list->size;
		if (list->eol)
			break ;
		list = list->next;
	}
	return (size);
}

char	*extract_line(t_list *list, int size, t_list **prev)
{
	char	*result;
	int		i;
	int		j;
	int		eol;

	result = (char *)malloc(sizeof (char) * (size + 1));
	if (result == 0)
		return (NULL);
	i = 0;
	while (list)
	{
		eol = list->eol;
		*prev = list->next;
		j = 0;
		while (list->str[j])
			result[i++] = list->str[j++];
		free(list->str);
		free(list);
		if (eol)
			break ;
		list = *prev;
	}
	result[i] = 0;
	return (result);
}

char	*get_next_line(int fd)
{
	static t_list	*prevlist[1024];
	t_list			*first;
	char			*result;

	first = prevlist[fd];
	if (fd < 0)
		return (NULL);
	if (make_list(fd, &first) == 0)
		return (NULL);
	if (first == 0)
		return (NULL);
	result = extract_line(first, get_size(first), &(prevlist[fd]));
	return (result);
}
/*
#include <fcntl.h>
int	main()
{
	int		fd;
	char	*result;

	fd = open ("testfile", O_RDWR);
	while(result = get_next_line(fd))
	{
		printf("%s\n", result);
		free(result);
	}
}
*/