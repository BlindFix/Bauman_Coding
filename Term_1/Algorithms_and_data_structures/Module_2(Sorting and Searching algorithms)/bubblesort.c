void	bubblesort(unsigned long nel,
	int (*compare)(unsigned long i, unsigned long j),
	void (*swap)(unsigned long i, unsigned long j))
{
	long	left = 0, right = nel - 1;

	for (long i = 1; left < right; i *= -1)
	{
		for(long j = (i > 0) ? left : right; j != ((i > 0) ? right : left); j += i)
		{
			(i * compare(j, j + i) > 0) ? swap(j, j + i) : 1;
		}
		(i > 0) ? (right--) : (left++);
	}
}
