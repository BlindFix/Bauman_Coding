#include <stdio.h>

unsigned int	pow_2(unsigned int x)
{
	unsigned int	res = 1;

	while (x-- > 0)
		res *= 2;

	return (res);
}

unsigned int	set_mnoj()
{
	unsigned int	count;
	unsigned int	mnoj = 0;
	unsigned int	x;

	scanf(" %u", &count);

	while (count-- > 0)
	{
		scanf(" %u", &x);

		mnoj = mnoj | pow_2(x);
	}

	return (mnoj);
}

int	main(void)
{
	unsigned int	A = set_mnoj();
	unsigned int	B = set_mnoj();
	unsigned int	res = A & B;
	unsigned int	count = 0;
	unsigned int	first = 1;

	while (count < 32)
	{
		if ((res & pow_2(count)) != 0)
		{
			if (first == 1)
			{
				printf("%u", count);
				first = 0;
			}
			else
				printf(" %u", count);
		}
		count++;
	}
	return (0);
}
