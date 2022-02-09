#include <stdio.h>

long	is_power2(long sum)
{
	while ((sum > 0) && (sum % 2 == 0))
		sum /= 2;

	if (sum == 1)
		return (1);
	return (0);
}

long	recursive_brute_check(int nado, int vsego, int *arr, int index, long sum_node, long sum_arr)
{
	if (nado == 0)
		return (is_power2(sum_node) + is_power2(sum_arr - sum_node));

	long now_res = 0;

	for (int i = index; i <= (vsego - nado); i++)
		now_res += recursive_brute_check(nado - 1, vsego, arr, index + 1, sum_node + arr[i], sum_arr);

	return (now_res);
}

long	sum_arr(int	*arr, int n)
{
	long	summ = 0;

	for (int i = 0; i < n; i++)
		summ += (long)arr[i];

	return (summ);
}

int	main(void)
{
	int		n;
	long	count = 0;
	scanf(" %d", &n);				// вводим количество чиел

	int	arr[n];
	for (int i = 0; i < n; i++)		// заполняем массив чисел
		scanf(" %d", &arr[i]);

	long	summ = sum_arr(arr, n); // задаём сумму чисел во всём массиве
	for (int i = 0; i <= ((n - 1)/ 2); i++)
	{
		count += recursive_brute_check(i, n, arr, 0, 0, summ);
	}

	if (n % 2 == 0)
		count += (recursive_brute_check(n / 2, n, arr, 0, 0, summ));

	printf("%ld", count);

	return (0);
}
