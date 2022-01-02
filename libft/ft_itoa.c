#include "libft.h"
static size_t	count_decimal(int n);
static void		populate_result(long n, int i, char *str);

char	*ft_itoa(int n)
{
	int		i;
	char	*result;
	long	ln;

	ln = n;
	n = 0;
	if (ln < 0)
	{
		ln = -ln;
		n = 1;
	}
	result = malloc(count_decimal(ln) + n + 1);
	if (!result)
		return (NULL);
	i = count_decimal(ln) + n - 1;
	result[i + 1] = '\0';
	if (n)
		result[0] = '-';
	if (!ln)
		result[i] = '0';
	populate_result(ln, i, result);
	return (result);
}

static void	populate_result(long n, int i, char *str)
{
	while (n && str)
	{
		str[i] = (n % 10) + '0';
		n /= 10;
		i--;
	}
}

static size_t	count_decimal(int n)
{
	size_t	i;

	if (!n)
		return (1);
	i = 0;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}
