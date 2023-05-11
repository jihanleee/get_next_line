/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 20:56:22 by jihalee           #+#    #+#             */
/*   Updated: 2023/05/11 21:05:23 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
