#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

struct String {
	char	str[1001];
	int		a_count;
};

int aaas(char *str)
{
	int count = 0;

	while (*str)
		*(str++) == 'a' ? count++ : 1;

	return (count);
}

int	compare_by_aaa(const void *a, const void *b)
{
	return (((struct String *)a)->a_count - ((struct String *)b)->a_count);
}

void swap_elems(void *s1, void *s2, long width)
{
	unsigned char temp;

	for (long i = 0; i < width; i++)
	{
		temp = *((unsigned char *)s1 + i);
		*((unsigned char *)s1 + i) = *((unsigned char *)s2 + i);
		*((unsigned char *)s2 + i) = temp;
	}
}

void Heapify(int (*compare)(const void *a, const void *b), long i, long n,void *base, long width)
{
	long l, r, j;
	while (1)
	{
		l = 2 * i + 1;
		r = l + 1;
		j = i;
		if ((l < n) && (compare((unsigned char *)base + i * width, (unsigned char *)base + l * width) < 0))
			i = l;
		if ((r < n) && (compare((unsigned char *)base + i * width, (unsigned char *)base + r * width) < 0))
			i = r;
		if (i == j)
			break;
		swap_elems((unsigned char *)base + i * width, (unsigned char *)base + j * width, width);
	}
}

void BuildHeap(int (*compare)(const void *a, const void *b), long n, void *base, long width)
{
	long i = (n / 2) - 1;
	while (i >= 0)
	{
		Heapify(compare, i, n, base, width);
		i--;
	}
}

void hsort(void *base, size_t nel, size_t width,
		int (*compare)(const void *a, const void *b))
{
	BuildHeap(compare, nel, base, width);
	long i = nel - 1;
	while (i > 0)
	{
		swap_elems(base, (void *)((unsigned char *)base + i * width), width);
		Heapify(compare, 0, i, base, width);
		i--;
	}
}

int	main(void)
{
	long n;

	scanf(" %ld ", &n);

	struct String strs[n];
	for (long i = 0; i < n; i++)
	{
		fgets(strs[i].str, 1001, stdin);
		strs[i].a_count = aaas(strs[i].str);
	}

	hsort(strs, n, sizeof(strs), compare_by_aaa);

	for (long i = 0; i < n; i++)
		printf("%s", strs[i].str);

	return (0);
}
