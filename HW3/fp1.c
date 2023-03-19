#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct {
	int u;
	int v;
	int cost;
} edge;

edge* minheap;
int parent[10001];
int numofheap = 0;

void heap_insert(edge* heap, edge e);
edge heap_delete(edge* heap);
int find(int x);

int main(int argc, char** argv)
{
	char* infile;
	if (argc != 2)
	{
		printf("usage: ./fp1 input_filename\n");
		return 0;
	}
	infile = argv[1];

	FILE* input = fopen(infile, "r");
	FILE* result = fopen("fp1_result.txt", "w");
	if (input == NULL)
	{
		printf("The input file does not exist.\n");
		return 0;
	}

	int V, E;
	fscanf(input, "%d %d", &V, &E);
	minheap = malloc(sizeof(edge) * (E + 1));
	for (int i = 0; i < E; i++)
	{
		edge e;
		fscanf(input, "%d %d %d", &e.u, &e.v, &e.cost);
		heap_insert(minheap, e);
	}
	for (int i = 0; i < V; i++)
		parent[i] = i;

	clock_t start = clock();
	int ans = 0;
	for (int i = 0; i < E; i++)
	{
		edge e = heap_delete(minheap);
		if (find(e.u) != find(e.v))
		{
			fprintf(result, "%d %d %d\n", e.u, e.v, e.cost);
			parent[find(e.v)] = parent[find(e.u)];
			ans += e.cost;
		}
	}

	fprintf(result, "%d\n", ans);

	int cnt = 0;
	for (int i = 0; i < V; i++)
	{
		if (parent[i] == i)
			cnt++;
	}
	if (cnt >= 2)
		fprintf(result, "DISCONNECTED");
	else
		fprintf(result, "CONNECTED");
	clock_t end = clock();

	printf("output written to fp1_result.txt.\n");
	float res = (float)(end - start) / CLOCKS_PER_SEC;
	printf("running time: %f seconds", res);

	fclose(input);
	fclose(result);
	return 0;
}

void heap_insert(edge* heap, edge e)
{
	int idx = ++numofheap;
	while (idx != 1 && e.cost < heap[idx / 2].cost)
	{
		heap[idx] = heap[idx / 2];
		idx /= 2;
	}
	heap[idx] = e;
}

edge heap_delete(edge* heap)
{
	int parentidx = 1, childidx = 2;
	edge e = heap[1];
	edge temp = heap[numofheap--];
	while (childidx <= numofheap)
	{
		if (childidx<numofheap && heap[childidx].cost>heap[childidx + 1].cost)
			childidx++;
		if (temp.cost <= heap[childidx].cost)
			break;
		heap[parentidx] = heap[childidx];
		parentidx = childidx;
		childidx *= 2;
	}
	heap[parentidx] = temp;
	return e;
}

int find(int x)
{
	if (x == parent[x])
		return x;
	else
		return parent[x] = find(parent[x]);
}