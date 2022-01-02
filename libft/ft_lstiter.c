#include "libft.h"
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*i;

	i = lst;
	while (i)
	{
		f(i->content);
		i = i->next;
	}
}
