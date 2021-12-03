#include <stdio.h>

int	main(void)
{
	long	n;
	long	x0;
	long	res0 = 0;
	long	res1 = 0;
	long	x;

	scanf(" %ld %ld", &n, &x0);
	while (n > 0)
	{
		scanf(" %ld", &x);
		res0 = (res0 * x0) + x;
		res1 = (res1 * x0) + x * (n--);
	}

	scanf(" %ld", &x);
	res0 = (res0 * x0) + x;

	printf("%ld %ld", res0, res1);
	return (0);
}
