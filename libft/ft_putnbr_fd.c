#include "libft.h"
static size_t	count_decimal(int n);

void	ft_putnbr_fd(int n, int fd)
{
	int		count;
	int		i;
	char	result[10];
	long	ln;

	ln = n;
	if (n < 0)
	{
		ln *= -1;
		write(fd, "-", 1);
	}
	else if (ln == 0)
	{
		write (fd, "0", 1);
		return ;
	}
	count = count_decimal(ln);
	i = count - 1;
	while (ln)
	{
		result[i] = (ln % 10) + '0';
		ln /= 10;
		i--;
	}
	write(fd, &result, count);
}

static size_t	count_decimal(int n)
{
	size_t	i;

	i = 0;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}
