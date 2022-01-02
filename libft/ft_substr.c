#include "libft.h"
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*cpy;
	size_t	i;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (start > s_len)
	{
		cpy = malloc(1);
		cpy[0] = '\0';
		return (cpy);
	}
	if (s_len < len)
		len = s_len;
	if (s_len - start < len)
		len = s_len - start;
	cpy = malloc(len + 1);
	i = 0;
	if (!cpy)
		return (cpy);
	while (i < len && s[i])
		cpy[i++] = s[start++];
	cpy[i] = '\0';
	return (cpy);
}
