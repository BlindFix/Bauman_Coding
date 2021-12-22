#include <stdio.h>

void	set_array(long int* arr)
{
	int	i = 0;

	while (i < 8)
	{
		scanf(" %ld", &arr[i++]);
	}
}

int	main(void)
{
	long int	A[8];
	long int	Used[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int			i = 0;
	int			j;
	long int	x;

	set_array(A);

	while (i < 8)
	{
		scanf(" %ld", &x);

		j = 0;
		while (j < 8)
		{
			if ((A[j] == x) && (Used[j] == 0))
			{
				Used[j] = 1;
				break;
			}

			j++;
		}

		if (j == 8)
			break;
		i++;
	}

	if (i == 8)
	{
		printf("yes");
	}
	else
		printf("no");

	return (0);
}
