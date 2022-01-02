#include "libft.h"
void	*ft_memset(void *dest, int c, size_t len)
{
	size_t	i;
	char	*ret;

	ret = dest;
	i = 0;
	while (i < len)
	{
		ret[i] = (unsigned char) c;
		i++;
	}
	return (dest);
}
