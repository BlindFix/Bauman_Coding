#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>

enum entryState{
	STATE_EMPTY = 0,
	STATE_FREED,
	STATE_FULL,
};

typedef struct{
	enum	entryState state;
	int		value;
	int		key;
} MapEntry;

typedef struct{
	int	length;
	MapEntry *map;
} HashMap;

HashMap *NewHashMap(int length)
{
	HashMap *map = (HashMap *)malloc(sizeof(HashMap));
	map->length = length;
	map->map = (MapEntry *)calloc(length, sizeof(MapEntry));

	return (map);
}

int At(HashMap *map, int key)
{
	int h = ((key % map->length) + map->length) % map->length;
	while (map->map[h].state != STATE_EMPTY)
	{
		if ((key == map->map[h].key) && (map->map[h].state == STATE_FULL))
			return (map->map[h].value);
		h = (h + 1) % map->length;
	}
	return (0);
}

void Assign(HashMap *map, int key, int value)
{
	int h = ((key % map->length) + map->length) % map->length;
	while (map->map[h].state != STATE_EMPTY)
	{
		if ((key == map->map[h].key) && (map->map[h].state == STATE_FULL))
		{
			map->map[h].value = value;
			return;
		}
		h = (h + 1) % map->length;
	}

	h = ((key % map->length) + map->length) % map->length;
	while (map->map[h].state == STATE_FULL)
	{
		h = (h + 1) % map->length;
	}
	map->map[h].state = STATE_FULL;
	map->map[h].key = key;
	map->map[h].value = value;
}

void Delete(HashMap *map, int key)
{
	int h = ((key % map->length) + map->length) % map->length;
	while (map->map[h].state != STATE_EMPTY)
	{
		if ((key == map->map[h].key) && (map->map[h].state == STATE_FULL))
		{
			map->map[h].state = STATE_FREED;
			if (map->map[(h + 1) % map->length].state == STATE_EMPTY)
			{
				while (map->map[h].state == STATE_FREED)
				{
					map->map[h].state = STATE_EMPTY;
					h = (h - 1 + map->length) % map->length;
				}
			}
		}
		h = (h + 1) % map->length;
	}
}

int	main(void)
{
	int	n, x, p;
	long long count = 0;
	scanf("%d", &n);

	p = 0;
	HashMap *map = NewHashMap(n + 3);
	Assign(map, 0, 1);

	for(int i = 0; i < n; i++)
	{
		scanf("%d", &x);
		p ^= x;
		count += At(map, p);
		Assign(map, p, At(map, p) + 1);
	}

	printf("%lld\n", count);

	free(map->map);
	free(map);

	return (0);
}
