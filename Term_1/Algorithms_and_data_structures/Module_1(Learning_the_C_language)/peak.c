// #include <stdio.h>
// #include <stdlib.h>
// unsigned long arr[] = {0, 1, 2, 3, 6, 2, 0};

// int	compare(unsigned long i, unsigned long j)
// {
// 	return ((arr[i] < arr[j]) ? 1 : 0);
// }

unsigned long peak(unsigned long nel,
		int (*less)(unsigned long i, unsigned long j))
{
	unsigned long with_prev = 1, with_next, i = 0;

	for ( ; i < nel - 1; i++)
	{
		(less(i, i + 1) == 0) ? (with_next = 1) : (with_next = 0);
		if (with_prev && with_next)
			break;

		(with_next == 1) ? (with_prev = 0) : (with_prev = 1);
	}
	return i;
}

// int	main(void)
// {
// 	printf("%lu", peak(7, compare));

// 	return (0);
// }
