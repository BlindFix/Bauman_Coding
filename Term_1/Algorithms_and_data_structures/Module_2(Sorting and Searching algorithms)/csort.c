#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	count;

	count = 0;
	if (!dstsize)
	{
		while (src[count] != '\0')
			count++;
		return (count);
	}
	while ((count < dstsize - 1) && (src[count] != '\0'))
	{
		dst[count] = src[count];
		count++;
	}
	dst[count] = '\0';
	while (src[count] != '\0')
		count++;
	return (count);
}

void	my_free(char **strings, size_t count)
{
	for (size_t i = 0; i < count; i++)
		free(strings[i]);
	free(strings);
}

char *concat_with_spases(char **s, int n)
{
	size_t arr[n], size_all_strings = 0, x;
	char *result, *result_copy;

	for(size_t i = 0; i < (unsigned long)n; i++) // заполняем масссив длин строк и запоминаем общую длину
	{
		x = strlen(s[i]);
		arr[i] = x;
		size_all_strings += x;
	}

	result = (char *)calloc(size_all_strings + n + 1, sizeof(char)); // выделяем место под результирующую строку
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
		*result_copy = ' ';
		result_copy++;
	}
	result_copy--;
	*result_copy = '\0';

	return (result);
}

int wcount(char *s)
{
	int	prev_space = 1, count = 0;

	while(*s)								// пока не конец строки
	{
		if (!isspace(*s))						// если сейчас не пробел
		{
			if (prev_space)					// и если до этого был пробел,
				count++;					// то это начало нового словаа.
			prev_space = 0;					// для следующего символа важно знать, что этот не был пробельным
		}
		else prev_space = 1;

		s++;								// к следующему символу
	}

	return (count);
}

long	compare_strs(char *s1, char *s2)
{
	return (strlen(s1) - strlen(s2));
}

static char	*ft_get_word(char const *s, char c)
{
	int		len;
	char	*word;

	len = 0;
	while (s[len] && (s[len] != c) && (s[len] != '\n'))
		len++;
	word = calloc(sizeof(char), len + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, s, len + 1);
	return (word);
}

static char	**ft_free(char **s_arr)
{
	int	i;

	i = 0;
	while (s_arr[i] != 0)
		free(s_arr[i++]);
	free(s_arr);
	return (NULL);
}

static char	**ft_free2(char **s_arr)
{
	char	**res;
	int		c;

	c = 0;
	while (s_arr[c])
		c++;
	res = calloc(sizeof(char *), c + 1);
	if (!res)
		return (NULL);
	c = 0;
	while (s_arr[c])
	{
		res[c] = s_arr[c];
		c++;
	}
	free(s_arr);
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**s_arr;
	int		is_prev_c;
	int		i;

	i = 0;
	is_prev_c = 1;
	if (!s)
		return (NULL);
	s_arr = calloc(sizeof(char *), (strlen(s) + 1) / 2 + 1);
	if (!s_arr)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			is_prev_c = 1;
		else if (is_prev_c)
		{
			s_arr[i] = ft_get_word(s, c);
			if (s_arr[i++] == 0)
				return (ft_free(s_arr));
			is_prev_c = 0;
		}
		s++;
	}
	return (ft_free2(s_arr));
}

void csort(char *src, char *dest)
{
	long	n = (long)wcount(src);
	long	count[n];
	char	**arr = ft_split(src, ' ');

	for(long i = 0; i < n; i++)
		count[i] = 0;

	long i;
	for (long j = 0; j < n - 1; j++)
	{
		i = j + 1;
		while (i < n)
		{
			if(compare_strs(arr[i], arr[j]) < 0)
				count[j] += 1;
			else count[i] += 1;

			i += 1;
		}
	}

	char *arr2[n];
	for(long i = 0; i < n; i++)
	{
		arr2[count[i]] = arr[i];
	}

	char *ans = concat_with_spases(arr2, n);
	strcpy(dest, ans);

	my_free(arr, n + 1);
	free(ans);
}

int	main(void)
{
	char	string[1001], string_answer[1001];

	fgets(string, 1001, stdin);
	csort(string, string_answer);

	printf("%s", string_answer);

	return(0);
}
