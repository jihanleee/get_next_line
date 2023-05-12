/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 20:56:22 by jihalee           #+#    #+#             */
/*   Updated: 2023/05/12 14:44:19 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	sub = (char *)malloc(sizeof (char) * (len + 1));
	if (sub == 0)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
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

	if (str == 0)
		return (NULL);
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

t_list	*ft_lstlast(t_list *lst)
{
	if (lst == 0)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
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
