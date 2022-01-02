#include "libft.h"
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*i;
	t_list	*newlst;
	t_list	*tmp;

	if (!lst)
		return (NULL);
	newlst = ft_lstnew(f(lst->content));
	i = lst->next;
	while (i)
	{
		tmp = ft_lstnew(f(i->content));
		if (!tmp)
		{
			ft_lstclear(&newlst, del);
			return (NULL);
		}
		ft_lstadd_back(&newlst, tmp);
		i = i->next;
	}
	return (newlst);
}
