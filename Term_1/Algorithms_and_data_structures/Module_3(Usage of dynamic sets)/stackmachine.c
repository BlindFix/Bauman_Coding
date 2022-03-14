#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct{
	size_t	length;
	size_t	cap;
	int		*array;
} Stack;

Stack * new_stack()
{
	Stack * my_stack;
	my_stack = (Stack *)malloc(sizeof(Stack));
	my_stack->length = 0;
	my_stack->cap = 0;
	my_stack->array = NULL;

	return (my_stack);
}

void	push(Stack * stack, int elem)
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

int		pop(Stack * stack)
{
	return (stack->array[--(stack->length)]);
}

int	main(void)
{
	int	n, a, b;
	char command [7];
	scanf("%d", &n);

	Stack * stack = new_stack();

	for(int i = 0; i < n; i++)
	{
		scanf("%s", command);
		if (!strcmp("CONST", command))
		{
			scanf("%d", &a);
			push(stack, a);
		}
		else if (!strcmp("ADD", command))
		{
			a = pop(stack);
			b = pop(stack);
			push(stack, a + b);
		}
		else if (!strcmp("SUB", command))
		{
			a = pop(stack);
			b = pop(stack);
			push(stack, a - b);
		}
		else if (!strcmp("MUL", command))
		{
			a = pop(stack);
			b = pop(stack);
			push(stack, a * b);
		}
		else if (!strcmp("DIV", command))
		{
			a = pop(stack);
			b = pop(stack);
			push(stack, a / b);
		}
		else if (!strcmp("MAX", command))
		{
			a = pop(stack);
			b = pop(stack);
			push(stack, (a > b) ? a : b);
		}
		else if (!strcmp("MIN", command))
		{
			a = pop(stack);
			b = pop(stack);
			push(stack, (a < b) ? a : b);
		}
		else if (!strcmp("NEG", command))
		{
			a = pop(stack);
			push(stack, -a);
		}
		else if (!strcmp("DUP", command))
		{
			a = pop(stack);
			push(stack, a);
			push(stack, a);
		}
		else if (!strcmp("SWAP", command))
		{
			a = pop(stack);
			b = pop(stack);
			push(stack, a);
			push(stack, b);
		}
	}

	printf("%d\n", pop(stack));

	free(stack->array);
	free(stack);

	return (0);
}
