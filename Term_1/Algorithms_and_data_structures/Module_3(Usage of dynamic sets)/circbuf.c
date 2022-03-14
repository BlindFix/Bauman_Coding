#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct{
	int head;
	int tail;
	int cap;
	int	length;
	int *arr;
} Queue;

void	InitQueue (Queue * q)
{
	q->head = 0;
	q->tail = 0;
	q->length = 0;
	q->cap = 4;
	q->arr = (int *)malloc(sizeof(int) * 4);
}

int		QueueEmpty(Queue * q)
{
	return (q->length == 0);
}

void	Enqueue(Queue * q, int	elem)
{
	if (q->length != q->cap)
	{
		q->arr[q->tail] = elem;
		q->tail = (q->tail + 1) % q->cap;
		q->length++;
	}
	else
	{
		int	*old_arr = q->arr;
		int	old_cap = q->cap;
		int	old_head = q->head;
		q->head = 0;
		q->tail = 0;
		q->length = 0;
		q->cap = old_cap * 2;
		q->arr = (int *)malloc(sizeof(int) * q->cap);
		for(int i = 0; i < old_cap; i++)
		{
			Enqueue(q, old_arr[(i + old_head) % old_cap]);
		}
		free(old_arr);
		Enqueue(q, elem);
	}
}

int	Dequeue(Queue * q)
{
	int res = q->arr[q->head];
	q->head = (q->head + 1) % q->cap;
	q->length--;
	return (res);
}

int	main(void)
{
	int	n, a;
	char command [7];
	scanf("%d", &n);

	Queue q;
	InitQueue(&q);

	for(int i = 0; i < n; i++)
	{
		scanf("%s", command);
		if (!strcmp("ENQ", command))
		{
			scanf("%d", &a);
			Enqueue(&q, a);
		}
		else if (!strcmp("DEQ", command))
		{
			printf("%d\n", Dequeue(&q));
		}
		else if (!strcmp("EMPTY", command))
		{
			printf("%s\n", QueueEmpty(&q) ? "true" : "false");
		}
	}

	free(q.arr);

	return (0);
}
