#include "libft.h"
void	ft_lstadd_back(t_list **list, t_list *new)
{
	t_list	*i;

	if (!*list)
		*list = new;
	else
	{
		i = ft_lstlast(*list);
		i->next = new;
	}
}
