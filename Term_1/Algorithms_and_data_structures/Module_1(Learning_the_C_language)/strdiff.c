// #include <unistd.h>
// #include <string.h>
// #include <stdlib.h>
// #include <stdio.h>

int strdiff(char *a, char *b)
{
	int	until = 0;

	for ( ; (*a == *b) && (*a != 0); a++, b++)
		until += 8;

	if (*a == *b)
		return (-1);

	for (unsigned char my_a = *a, my_b = *b, pow_2 = 1; (my_a & pow_2) == (my_b & pow_2); pow_2 *= 2)
		until++;

	return (until);
}

// int	main(void)
// {
// 	char s1[] = "ai", s2[] = "aa";

// 	printf("%d", strdiff(s1, s2));

// 	return (0);
// }
