#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct PtreeNode

{
	struct PtreeNode *children[26];
	int count;
	int has_leaf;
} PtreeNode;

typedef struct

{
	PtreeNode *children[26];
} Ptree;

PtreeNode *NewPtreeNode()

{
	PtreeNode *node = malloc(sizeof(PtreeNode));
	node->count = 0;
	node->has_leaf = 0;
	for (int i = 0; i < 26; i++)

	{
		node->children[i] = NULL;
	}
	return node;
}


void PtreeNodeDestroy(PtreeNode *node)

{
	if (node == NULL)

	{
		return;
	}
	for(int i = 0; i < 26; i++)

	{
		PtreeNodeDestroy(node->children[i]);
	}
	free(node);
}

void PtreeDelete(Ptree *ptree, char *str)

{
	PtreeNode **node;

	node = ptree->children;
	while(*str)

	{
		node[*str - 'a']->count--;
		if (node[*str - 'a']->count == 0)

		{
			PtreeNodeDestroy(node[*str - 'a']);
			node[*str - 'a'] = NULL;
			return;
		}
		node = node[*str - 'a']->children;
		++str;
	}
}

void PtreeInsert(Ptree *ptree, char *str)

{
	PtreeNode **node;
	char *or_str;

	or_str = str;
	node = ptree->children;
	while(*str)

	{
		if (node[*str - 'a'] == NULL)

		{
			node[*str - 'a'] = NewPtreeNode();
		}
		node[*str - 'a']->count++;

		if (*(str + 1) == 0)

		{
			if (node[*str - 'a']->has_leaf)

			{
				PtreeDelete(ptree, or_str);
			}
			node[*str - 'a']->has_leaf = 1;
		}
		node = node[*str - 'a']->children;
		++str;
	}
}


int PtreePrefix(Ptree *ptree, char *str)

{
	PtreeNode **node;

	node = ptree->children;
	while(*str)

	{
		if (node[*str - 'a'] == NULL)

		{
			break;
		}
		if (*(str + 1) == 0)

		{
			return node[*str - 'a']->count;
		}
		node = node[*str - 'a']->children;
		++str;
	}
	return 0;
}

void PtreeDestroy(Ptree *ptree)

{
	for(int i = 0; i < 26; i++)

	{
		PtreeNodeDestroy(ptree->children[i]);
	}
	free(ptree);
}

int main()

{
	Ptree *ptree;
	ptree = (Ptree *)NewPtreeNode();

	int n;
	scanf("%i", &n);

	char *s = malloc(100005);
	char command[100];

	for (int i = 0; i < n; i++)

	{
		scanf("%s", command);
		if (!strcmp(command, "INSERT"))

		{
			scanf("%s", s);
			PtreeInsert(ptree, s);
		} else if (!strcmp(command, "DELETE"))

		{
			scanf("%s", s);
			PtreeDelete(ptree, s);
		} else if (!strcmp(command, "PREFIX"))

		{
			scanf("%s", s);
			printf("%i\n", PtreePrefix(ptree, s));
		}
	}

	free(s);
	PtreeDestroy(ptree);
}
