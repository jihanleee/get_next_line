/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 15:50:05 by jihalee           #+#    #+#             */
/*   Updated: 2023/05/09 23:09:59 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

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
		del(current->content);
		free(current);
		current = next;
	}
	*lst = 0;
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

t_list	*ft_lstnew(void *content)
{
	t_list	*new;
	char	*eol;

	new = (t_list *)malloc(sizeof (t_list));
	if (new == 0)
		return (NULL);
	new->next = 0;
	new->content = content;
	new->eol = 0;
	new->eof = 0;
	eol = ft_strchr((char *)content, '\n');
	if (eol != 0)
		new->eol = 1;
	return (new);
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

int	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

#include <string.h>

void	ft_lstprint(t_list *lst)
{
	while (lst)
	{
		printf("%s", (char *)(lst->content));
		printf("%d", lst->eol);
		lst = lst->next;
	}
}

void	extract_strs(t_list *first, char *result, char *str)
{
	int		i;
	int		j;
	t_list	*lst;

	lst = first;
	i = 0;
	while (lst)
	{
		j = 0;
		while (((char *)lst->content)[j] != '\n' && ((char *)lst->content)[j])
			result[i++] = ((char *)lst->content)[j++];
		if (lst->eol == 1)
		{
			result[i++] = '\n';
			break;
			j++;
		}
		lst = lst->next;
	}
	result[i] = '\0';
	i = 0;
	free(str);
	if (ft_strchr((char *)lst->content, '\n') && ((char *)lst->content)[j]);
		str = ft_strdup((char *)lst->content + j);
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*str;
	char		*result;
	int			bytes_read;
	t_list		*first;
	t_list		*current;
	int			size;

	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof (char));
	if (buf == 0)
		return (NULL);
	if (str == 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		buf[bytes_read] = '\0';
		if (bytes_read == 0 || bytes_read == -1)
		{
			free(buf);
			return (NULL);
		}
		first = ft_lstnew(ft_strdup(buf));
		current = first;
	}
	else if (str != 0)
		first = ft_lstnew(ft_strdup(str));
	size = ft_strlen(first->content);
	while (bytes_read && !current->eol)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == 0)
		{
			current->eof = 1;
			break ;
		}
		size += bytes_read;
		ft_lstadd_back(&current, ft_lstnew(ft_strdup(buf)));
		current = current->next;
	}
	if (current->eol)
		size = size + ft_strchr(current->content, '\n') - (char *)current->content;
	result = (char *)malloc(sizeof (char) * (size + 1));
	printf("size : %d\n", size);
	ft_lstprint(first);
	extract_strs(first, result, str);
	ft_lstclear(&first, &free);
	return (result);
}

#include <fcntl.h>
#include <stdio.h>

int	main()
{
	int	fd;
	char *buf;
	int	r_read;
	char *result;

	fd = open("testfile", O_RDWR);
	result = get_next_line(fd);
	while (result)
	{
		printf("%s", result);
		free(result);
		result = get_next_line(fd);
	}
	/*
	r_read = read(fd, buf, BUFFER_SIZE);
	printf ("r_read :%d, the string %s\n", r_read, buf);
	r_read = read(fd, buf, BUFFER_SIZE);
	printf ("r_read :%d, the string %s\n", r_read, buf);
	*/
	return (0);
}
