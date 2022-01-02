#include "libft.h"
void	*ft_calloc(size_t number, size_t size)
{
	void	*dst;

	dst = malloc(number * size);
	if (dst == 0)
		return (dst);
	ft_bzero(dst, number * size);
	return (dst);
}
