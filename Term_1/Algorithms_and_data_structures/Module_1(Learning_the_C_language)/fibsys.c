#include <stdio.h>

void	set_maxes(unsigned long x, unsigned long* max1, unsigned long* max2)
{
	unsigned long	t;

	while (*max1 + *max2 <= x)
	{
		t = *max1;
		*max1 +=  *max2;
		*max2 = t;
	}
}

int	main(void)
{
	unsigned long	x;
	unsigned long	max1 = 1;
	unsigned long	max2 = 1;
	unsigned long	t;

	scanf(" %lu", &x);

	set_maxes(x, &max1, &max2);
	while (max2 != 0)
	{
		if (max1 <= x)
		{
			printf("1");
			x -= max1;
		}
		else
			printf("0");

		t = max2;
		max2 = max1 - max2;
		max1 = t;
	}
	return (0);
}
