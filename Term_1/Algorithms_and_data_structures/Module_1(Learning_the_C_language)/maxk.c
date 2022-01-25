#include <stdio.h>

int	main(void)
{
	unsigned	n, k;

	scanf(" %u", &n);					// cчитываем размер массива

	long		arr[n], max_sum = 0, now_sum;

	for(size_t i = 0; i < n; i++)		// заполняем массив
		scanf(" %ld", &arr[i]);

	scanf(" %u", &k);					// считываем размер k

	for(size_t i = 0; i < k; i++)
		max_sum += arr[i];

	now_sum = max_sum;					// приравниваем значение счетчика нынешней суммы к значению суммы первых k элементов массива
	for(size_t i = k; i < n; i++)
	{
		now_sum += -arr[i - k] + arr[i];// на каждой итерации из нынешней суммы вычитаем самый "старый" элемент и добавляем новый
		if (now_sum > max_sum)
			max_sum = now_sum;			// если нынешняя сумма стала больше максимальной, то это новая максимальная сумма
	}

	printf("%ld", max_sum);
	return (0);
}
