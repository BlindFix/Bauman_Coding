#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	if (argc != 4)
	{
		printf("Usage: frame <height> <width> <text>");
		return (0);
	}

	long	height = atoi(argv[1]), width = atoi(argv[2]), len = strlen(argv[3]);
	char	*str = argv[3];

	if ((height < 3) || (width < len + 2))
	{
		printf("Error");
		return (0);
	}

	long str_h = (height - 1) / 2, spaces_1 = (width - len - 2) / 2, spaces_2 = (width - len - 2) - spaces_1;

	printf("%ld, %ld, %s, %ld, %ld\n", height, width, str, len, str_h);
	for (long i = 0; i < width; i++)
		printf("*");
	printf("\n");

	for (long i = 1; i < str_h; i++)
	{
		printf("*");
		for (long j = 0; j < width - 2; j++)
			printf(" ");
		printf("*");
		printf("\n");
	}

	printf("*");
	for (long j = 0; j < spaces_1; j++)
			printf(" ");
	printf("%s", str);
	for (long j = 0; j < spaces_2; j++)
			printf(" ");
	printf("*");
	printf("\n");

	for (long i = str_h + 1; i < height - 1; i++)
	{
		printf("*");
		for (long j = 0; j < width - 2; j++)
			printf(" ");
		printf("*");
		printf("\n");
	}

	for (long i = 0; i < width; i++)
		printf("*");
	printf("\n");

	return (0);
}
