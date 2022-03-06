#include <unistd.h>
#include <string.h>
#include <stdio.h>

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

char *fibstr(int n)
{
	char *s1, *s2;

	s1 = (char *)calloc(2, sizeof(char));
	s2 = (char *)calloc(2, sizeof(char));

	s1[0] = 'a';
	s2[0] = 'b';

	if (n < 1)
	{
		free(s1);
		free(s2);
		return (NULL);
	}

	if (n == 1)
	{
		free(s2);
		return (s1);
	}

	if (n == 2)
	{
		free(s1);
		return (s2);
	}

	for (int i = 3; i < n; i++)
	{

	}
}
