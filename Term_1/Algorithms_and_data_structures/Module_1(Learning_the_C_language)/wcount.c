#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#define BUFF_SIZE 1111

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

int	main(void)
{
	char	*string;

	string = (char *)calloc(BUFF_SIZE, sizeof(char));
	if (!string)
		return (137);

	fgets(string, BUFF_SIZE, stdin);
	printf("%d", wcount(string));

	free(string);
	return (0);
}
