#include "libft.h"
void	ft_bzero(void *b, size_t len)
{
	size_t	i;
	char	*str;

	str = b;
	i = 0;
	if (len == 0)
		return ;
	while (i < len)
	{
		str[i] = 0;
		i++;
	}
}
