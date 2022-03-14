#include <stdlib.h>
#include <stdio.h>

typedef struct {
	int value;
	int arr_ind;
} HeapEntry;

typedef struct{
	size_t	len;
	size_t	cap;
	HeapEntry *vector;
} Vector;

Vector * NewVector()
{
	Vector * my_vector;
	my_vector = (Vector *)malloc(sizeof(Vector));
	my_vector->len = 0;
	my_vector->cap = 0;
	my_vector->vector = NULL;

	return (my_vector);
}

void	VectorPush(Vector * vector, HeapEntry elem)
{
	if (vector->len < vector->cap)
		vector->vector[(vector->len)++] = elem;
	else
	{
		if (vector->cap == 0)
			vector->cap = 128;
		else
			vector->cap*=2;
		vector->vector = realloc(vector->vector, vector->cap * sizeof(HeapEntry));
		vector->vector[(vector->len)++] = elem;
	}
}

HeapEntry VectorPop(Vector * vector)
{
	return (vector->vector[--(vector->len)]);
}

void VectorDestroy(Vector *vector)
{
	free(vector->vector);
	free(vector);
}

typedef struct {
	Vector * heap;
} Heap;

Heap *NewHeap()
{
	Heap *heap;
	heap = (Heap *)malloc(sizeof(Heap));
	heap->heap = NewVector();
	return heap;
}

void HeapDestroy(Heap * heap)
{
	VectorDestroy(heap->heap);
	free(heap);
}

static size_t parent(size_t n)
{
	return (n - 1)/2;
}
static size_t left_child(size_t n)
{
	return n * 2 + 1;
}
static size_t right_child(size_t n)
{
	return n * 2 + 2;
}

static void heapifyup(Heap *heap, int i)
{

	i = heap->heap->len - 1;
	while (
			i <= (int)(heap->heap->len) &&
			parent(i) <= heap->heap->len &&
			heap->heap->vector[parent(i)].value > heap->heap->vector[i].value) {
		HeapEntry tmp;
		tmp = heap->heap->vector[i];
		heap->heap->vector[i] = heap->heap->vector[parent(i)];
		heap->heap->vector[parent(i)] = tmp;
		i = parent(i);
	}
}

static void heapifydown(Heap *heap, int i) {
	size_t max_child;
	size_t right;

	for(;;) {
		max_child = left_child(i);
		right = right_child(i);

		if (
				max_child < heap->heap->len &&
				right < heap->heap->len &&
				heap->heap->vector[max_child].value > heap->heap->vector[right].value) {
			max_child = right;
		}

		if (max_child < heap->heap->len &&
				heap->heap->vector[i].value > heap->heap->vector[max_child].value) {
			HeapEntry tmp;
			tmp = heap->heap->vector[i];
			heap->heap->vector[i] = heap->heap->vector[max_child];
			heap->heap->vector[max_child] = tmp;
			i = max_child;
		} else {
			break;
		}
	}
}

void HeapPush(Heap *heap, HeapEntry e)
{
	VectorPush(heap->heap, e);
	heapifyup(heap, heap->heap->len - 1);
}

HeapEntry HeapPop(Heap *heap)
{
	HeapEntry res;
	res = heap->heap->vector[0];

	heap->heap->vector[0] = heap->heap->vector[heap->heap->len - 1];
	VectorPop(heap->heap);
	heapifydown(heap, 0);

	return res;
}

int HeapEmpty(Heap *heap)
{
	return heap->heap->len == 0;
}


int main(void)
{
	int **arrays;
	int *sizes;
	int *consumed;
	int k;
	Heap *heap;

	int res_size;
	int res_index;
	int *res;

	scanf("%i", &k);
	arrays = (int **)malloc(sizeof(int *) * k);
	sizes = (int *)malloc(sizeof(int) * k);
	consumed = (int *)malloc(sizeof(int) * k);

	heap = NewHeap();

	res_size = 0;

	for(int i = 0; i < k; i++) {
		scanf("%i", &sizes[i]);
		res_size += sizes[i];
		arrays[i] = (int *)malloc(sizeof(int) * sizes[i]);
		consumed[i] = 0;
	}
	res = malloc(res_size * sizeof(int));

	for(int i = 0; i < k; i++) {

		for(int j = 0; j < sizes[i]; j++) {
			scanf("%i", &arrays[i][j]);
		}
	}
	for(int i = 0; i < k; i++) {
		if (consumed[i] < sizes[i]) {
			HeapPush(heap, (HeapEntry){
					.value = arrays[i][
					consumed[i]++
					],
					.arr_ind = i,
					});
		}
	}

	res_index = 0;
	while (!HeapEmpty(heap)) {
		HeapEntry e;
		e = HeapPop(heap);
		res[res_index++] = e.value;

		if (consumed[e.arr_ind] < sizes[e.arr_ind]) {
			HeapPush(heap, (HeapEntry){
					.value = arrays[e.arr_ind][
					consumed[e.arr_ind]++
					],
					.arr_ind = e.arr_ind,
					});
		}
	}

	for(int i = 0; i < res_size; i++) {
		printf("%i ", res[i]);
	}
	puts("");

	for(int i = 0; i < k; i++) {
		free(arrays[i]);
	}
	free(sizes);
	free(arrays);
	free(consumed);
	free(res);
	HeapDestroy(heap);

	return (0);
}
