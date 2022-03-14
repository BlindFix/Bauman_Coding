#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>

typedef struct MapEntry{
	int		value;
	int		key;
	struct MapEntry *next;
} MapEntry;

typedef struct{
	int	length;
	MapEntry **map;
} HashMap;

HashMap *NewHashMap(int length)
{
	HashMap *map = (HashMap *)malloc(sizeof(HashMap));
	map->length = length;
	map->map = (MapEntry **)calloc(length, sizeof(MapEntry *));

	return (map);
}

int At(HashMap *map, int key)
{
	int h = key % map->length;
	MapEntry *node;

	node = map->map[h];
	while (node)
	{
		if (node->key == key)
			return (node->value);
		node = node->next;
	}

	return (0);
}

void Assign(HashMap *map, int key, int value)
{
	int h = key % map->length;
	MapEntry **node;

	node = &(map->map[h]);
	while (*node)
	{
		if ((*node)->key == key)
		{
			(*node)->value = value;
			return;
		}
		node = &((*node)->next);
	}
	*node = malloc(sizeof(MapEntry));
	(*node)->next = NULL;
	(*node)->key = key;
	(*node)->value = value;
}

void Delete(HashMap *map, int key)
{
	int h = key % map->length;
	MapEntry **node, *tmp;

	node = &(map->map[h]);
	while (*node)
	{
		if ((*node)->key == key)
		{
			tmp = *node;
			*node = tmp->next;
			free(tmp);
			return;
		}
		node = &((*node)->next);
	}
}

void MapEntryDestroy(MapEntry *entry)
{
	if (entry == NULL)
		return;
	MapEntryDestroy(entry->next);
	free(entry);
}

void HashMapDestroy(HashMap *map)
{
	for (int i = 0; i < map->length; i++)
	{
		MapEntryDestroy(map->map[i]);
	}
	free(map->map);
	free(map);
}

int	main(void)
{
	int n, m, ii, v;
	char command[10];
	scanf("%d", &n);
	scanf("%d", &m);

	HashMap *map = NewHashMap(m);

	for(int i = 0; i < n; i++)
	{
		scanf("%s", command);
		if (!strcmp("ASSIGN", command))
		{
			scanf("%d", &ii);
			scanf("%d", &v);
			if (v == 0)
				Delete(map, ii);
			else Assign(map, ii, v);
		}
		else if (!strcmp("AT", command))
		{
			scanf("%d", &ii);
			printf("%d\n", At(map, ii));
		}
	}

	HashMapDestroy(map);

	return (0);
}
