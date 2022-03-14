#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>

typedef struct{
	size_t	length;
	size_t	cap;
	int		*array;
} Stack;

typedef struct{
	Stack * normalStack;
	Stack * maxStack;
} MaxStack;

typedef struct{
	MaxStack * pushed;
	MaxStack * popped;
} MaxQueue;

int	max(int a, int b)
{
	return (a > b ? a : b);
}

Stack * NewStack()
{
	Stack * my_stack;
	my_stack = (Stack *)malloc(sizeof(Stack));
	my_stack->length = 0;
	my_stack->cap = 0;
	my_stack->array = NULL;

	return (my_stack);
}

void StackDestroy(Stack * stack)
{
	free(stack->array);
	free(stack);
}

void	StackPush(Stack * stack, int elem)
{
	if (stack->length < stack->cap)
		stack->array[(stack->length)++] = elem;
	else
	{
		if (stack->cap == 0)
			stack->cap = 128;
		else
			stack->cap*=2;
		stack->array = realloc(stack->array, stack->cap * sizeof(int));
		stack->array[(stack->length)++] = elem;
	}
}

int		StackPop(Stack * stack)
{
	return (stack->array[--(stack->length)]);
}

MaxStack * NewMaxStack()
{
	MaxStack * my_stack;
	my_stack = (MaxStack *)malloc(sizeof(MaxStack));
	my_stack->normalStack = NewStack();
	my_stack->maxStack = NewStack();

	return (my_stack);
}

int	MaxStackPop (MaxStack * my_MaxStack)
{
	StackPop(my_MaxStack->maxStack);
	return(StackPop(my_MaxStack->normalStack));
}

int MaxStackEmpty (MaxStack * my_MaxStack)
{
	return (my_MaxStack->maxStack->length == 0);
}

int	MaxStackMax(MaxStack * my_MaxStack)
{
	if (MaxStackEmpty(my_MaxStack))
		 return (INT_MIN);
	return (my_MaxStack->maxStack->array[my_MaxStack->maxStack->length - 1]);
}

void MaxStackPush (MaxStack * my_MaxStack, int elem)
{
	StackPush(my_MaxStack->normalStack, elem);
	StackPush(my_MaxStack->maxStack, max(elem, MaxStackMax(my_MaxStack)));
}

void MaxStackDestroy(MaxStack * stack)
{
	StackDestroy(stack->maxStack);
	StackDestroy(stack->normalStack);
	free(stack);
}

void	InitQueue (MaxQueue * q)
{
	q->popped = NewMaxStack();
	q->pushed = NewMaxStack();
}

int		QueueEmpty(MaxQueue * q)
{
	return (MaxStackEmpty(q->popped) && MaxStackEmpty(q->pushed));
}

void	Enqueue(MaxQueue * q, int	elem)
{
	MaxStackPush(q->pushed, elem);
}

int	Dequeue(MaxQueue * q)
{
	if (MaxStackEmpty(q->popped))
	{
		while (!MaxStackEmpty(q->pushed))
		{
			MaxStackPush(q->popped, MaxStackPop(q->pushed));
		}
	}
	return (MaxStackPop(q->popped));
}

int Max (MaxQueue * q)
{
	return (max(MaxStackMax(q->popped), MaxStackMax(q->pushed)));
}

void MaxQueueDestroy (MaxQueue * q)
{
	MaxStackDestroy(q->popped);
	MaxStackDestroy(q->pushed);
}

int	main(void)
{
	int	n, a;
	char command [7];
	scanf("%d", &n);

	MaxQueue q;
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
		else if (!strcmp("MAX", command))
		{
			printf("%d\n", Max(&q));
		}
	}

	MaxQueueDestroy(&q);

	return (0);
}
