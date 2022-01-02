#include "libft.h"
void	*ft_memchr(const void *b, int c, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *) b;
	while (i < len)
	{
		if ((unsigned char)str[i] == (unsigned char) c)
			return ((void *)&str[i]);
		i++;
	}
	return (NULL);
}
