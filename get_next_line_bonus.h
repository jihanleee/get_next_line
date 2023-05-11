/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 19:52:52 by jihalee           #+#    #+#             */
/*   Updated: 2023/05/11 21:18:53 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_list
{
	char			*str;
	int				eol;
	int				size;
	struct s_list	*next;
}				t_list;

char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
t_list	*ft_lstnew(char *str, int size);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		add_to_list(char *buf, t_list **list);
int		make_list(int fd, t_list **list);
int		get_size(t_list *list);
char	*extract_line(t_list *list, int size, t_list **prev);
char	*get_next_line(int fd);

#endif
