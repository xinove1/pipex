#include "libft.h"
char	*ft_strdup(const char *str)
{
	char	*cpy;

	cpy = malloc(ft_strlen(str) + 1);
	if (cpy == 0)
		return (cpy);
	ft_strlcpy(cpy, str, ft_strlen(str) + 1);
	return (cpy);
}
