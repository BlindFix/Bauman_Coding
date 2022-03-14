#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <ctype.h>

struct Elem {
	struct Elem *next;
	char *word;
};

struct Elem *InitElem()
{
	struct Elem *res;

	res = (struct Elem*)malloc(sizeof(struct Elem));
	return (res);
}

int		ListLength(struct Elem *list)
{
	int count = 0;
	while(list != NULL)
	{
		count++;
		list = list->next;
	}
	return (count);
}

void	ListSwap(struct Elem *prev, struct Elem *now)
{
	struct Elem *tmp;
	prev->next = now->next;
	tmp = now->next->next;
	now->next->next = now;
	now->next = tmp;
}

int	ListCompare(struct Elem *x, struct Elem *y)
{
	return ((int)(strlen(x->word) - strlen(y->word)));
}

struct Elem *bsort(struct Elem *list)
{
	int elemCount = ListLength(list);
	struct Elem *now, *prev;

	prev = InitElem();
	prev->next = list;
	list = prev;

	for (int i = elemCount; i > 1; i--)
	{
		prev = list;
		now = list->next;
		for (int j = 1; (j < i) && (now != NULL) && (now->next != NULL); j++, prev = now, now = now->next)
		{
			if(ListCompare(now, now->next) > 0)
				ListSwap(prev, now);
		}
	}
	now = list->next;
	free(list);
	return (now);
}
//Начало копипаста сплита из второго модуля
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

int	main(void)
{
	char str[1003];
	fgets(str, 1003, stdin);

	int		n = (int)wcount(str);
	char	**arr = ft_split(str, ' ');

	struct Elem *list = NULL, *tmp;
	for (int i = n - 1; i >= 0; i--)
	{
		tmp = InitElem();
		tmp->next = list;
		tmp->word = arr[i];
		list = tmp;
	}

	list = bsort(list);

	for (int i = 1; i < n; i++)
	{
		printf("%s ", list->word);
		tmp = list;
		list = list->next;
		free (tmp->word);
		free (tmp);
	}
	printf("%s\n", list->word);

	free (list->word);
	free (list);
	free (arr);

	return (0);
}
