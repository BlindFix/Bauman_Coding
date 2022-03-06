#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char *concat_two(char *s1, char *s2)
{
	char *result, *now;
	size_t i = 0;

	result = (char *)calloc(strlen(s1) + strlen(s2) + 1, sizeof(char));

	now = s1;
	for ( ; *s1 != '\0'; i++, s1++)
		result[i] = *s1;
	for ( ; *s2 != '\0'; i++, s2++)
		result[i] = *s2;

	result[i] = '\0';

	return (result);
}

char *fibstr(int n)
{
	char *s1, *s2, *new;

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

	for (int i = 3; i <= n; i++)
	{
		new = concat_two(s1, s2);
		free(s1);
		s1 = s2;
		s2 = new;
	}

	free (s1);

	return (s2);
}

int	main(void)
{
	int		n;
	char	*result;

	scanf("%d", &n);

	result = fibstr(n);
	printf("%s", result);

	free(result);

	return (0);
}
