#include "libft.h"
int	ft_memcmp(const void *b1, const void *b2, size_t len)
{
	size_t	i;

	i = 0;
	if (!len)
		return (0);
	while (i < len && ((char *) b1)[i] == ((char *) b2)[i])
		i++;
	if (i == len)
		i--;
	return ((unsigned char)((char *) b1)[i] - (unsigned char)((char *) b2)[i]);
}
