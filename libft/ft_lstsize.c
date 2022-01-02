#include "libft.h"
int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*j;

	i = 0;
	j = lst;
	while (j)
	{
		j = j->next;
		i++;
	}
	return (i);
}
