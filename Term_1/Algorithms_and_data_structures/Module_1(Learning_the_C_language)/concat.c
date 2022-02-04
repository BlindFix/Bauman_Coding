#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void	my_free(char **strings, size_t count)
{
	for (size_t i = 0; i < count; i++)
		free(strings[i]);
	free(strings);
}

char *concat(char **s, int n)
{
	size_t arr[n], size_all_strings = 0, x;
	char *result, *result_copy;

	for(size_t i = 0; i < (unsigned long)n; i++) // заполняем масссив длин строк и запоминаем общую длину
	{
		x = strlen(s[i]);
		arr[i] = x;
		size_all_strings += x;
	}

	result = (char *)calloc(size_all_strings + 1, sizeof(char)); // выделяем место под результирующую строку
	if (!result)
		return (NULL);

	result_copy = result;
	for(size_t i = 0; i < (unsigned long)n; i++) // последовательно заполняем результирующую строку
	{
		for(size_t j = 0; j < arr[i]; j++)
		{
			*result_copy = s[i][j];
			result_copy++;
		}
	}

	return (result);
}

int	main(void)
{
	unsigned long	count;
	char			**strings;
	char			*result;

	scanf(" %lu", &count);

	strings = (char **)calloc(count, sizeof(char *));
	if (!strings)
		return (137);
	for (size_t i = 0; i < count; i++)
	{
		strings[i] = (char *)calloc(1001, sizeof(char));
		if (!strings[i])
		{
			my_free(strings, i);
			return (137);
		}
		scanf(" %s", strings[i]);
	}

	result = concat(strings, count);
	printf("%s", result);

	my_free(strings, count);
	free(result);
	return (0);
}
