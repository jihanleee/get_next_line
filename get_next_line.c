/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:50:05 by jihalee           #+#    #+#             */
/*   Updated: 2023/05/11 19:41:16 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <string.h>

void	ft_lstprint(t_list *lst)
{
	while (lst)
	{
		printf("===string====\n");
		printf("%s\n", (char *)(lst->str));
		printf("====eol===\n");
		printf("eol : %d\n", lst->eol);
		printf("====size===\n");
		printf("size : %d\n", lst->size);
		printf("=======\n");
		lst = lst->next;
	}
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
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

t_list	*ft_lstnew(char *str, int size)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof (t_list));
	if (new == 0)
		return (NULL);
	new->next = 0;
	new->str = str;
	if (str[size - 1] == '\n')
		new->eol = 1;
	else
		new->eol = 0;
	new->size = size;
	return (new);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (lst == 0 || new == 0)
		return ;
	if (*lst == 0)
		*lst = new;
	else
	{
		while ((*lst)->next)
			lst = &((*lst)->next);
		(*lst)->next = new;
	}
}

int	add_to_list(char *buf, t_list **list)
{
	char	*str;
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
		buf[size_read] = '\0';
		if (size_read <= 0)
			break;
		if (add_to_list(buf, list) == 1)
			break;
	}
	free(buf);
	if (size_read == -1)
		return (0);
	return (1);
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next;

	if (lst == 0)
		return ;
	if (del == 0)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		del(current->str);
		free(current);
		current = next;
	}
	*lst = 0;
}

char	*get_next_line(int fd)
{
	static t_list	*prevlist;
	t_list			*first;
	char			*result;

	first = prevlist;
	if (fd < 0)
		return (NULL);
	if (make_list(fd, &first) == 0)
		return (0);
	ft_lstprint(first);
	ft_lstclear(&first, free);
}

#include <fcntl.h>
int	main()
{
	int	fd;

	fd = open ("testfile", O_RDWR);
	get_next_line(fd);
}
