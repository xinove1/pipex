#include "libft.h"
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		i;
	int		j;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	join = malloc(i + j + 1);
	if (join == 0)
		return (join);
	ft_memcpy(join, s1, i);
	ft_memcpy(&join[i], s2, j);
	join[j + i] = '\0';
	return (join);
}
