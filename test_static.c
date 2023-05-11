#include "get_next_line.h"
#include <stdio.h>

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

t_list	*ft_lstnew(char *str)
{
	t_list	*new;
	char	*eol;

	new = (t_list *)malloc(sizeof (t_list));
	if (new == 0)
		return (NULL);
	new->str = str;
	new->next = 0;
	new->eol = 0;
	if (eol != 0)
		new->eol = 1;
	return (new);
}

void	ft_lstprint(t_list *lst)
{
	while (lst)
	{
		printf("%s", (char *)(lst->str));
		lst = lst->next;
	}
}
void	test_static(int i)
{
	static t_list	*list;

	if (i == 1)
	{
		list = ft_lstnew(ft_strdup("1st"));
		list->next = ft_lstnew(ft_strdup("2nd"));
		list->next->next = ft_lstnew(ft_strdup("3nd"));
		ft_lstprint(list);
	}
	else
		ft_lstprint(list);
}

int	main()
{
	test_static(1);
	test_static(2);
	return (0);
}