#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
	struct Node* prev;
	int data;
	struct Node* next;
};
typedef struct Node* listPointer;

void print_forward(listPointer list);
void print_reverse(listPointer list);

int main(int argc, char** argv)
{
	char* infile;
	if (argc != 2)
	{
		printf("usage: ./hw2 input_filename\n");
		return 0;
	}
	infile = argv[1];

	FILE* input = fopen(infile, "r");
	if (input == NULL)
	{
		printf("The input file does not exist.\n");
		return 0;
	}

	FILE* result = fopen("hw2_result.txt", "w");

	listPointer head = NULL, curr;
	char command[10];

	while (fscanf(input, "%s", command) != EOF)
	{
		command[strlen(command)] = '\0';
		if (!strcmp(command, "INSERT"))
		{
			int data;
			fscanf(input, "%d", &data);
			listPointer newnode = (listPointer)malloc(sizeof(struct Node));
			newnode->data = data;
			if (head == NULL)
			{
				head = newnode;
				head->prev = head, head->next = head;
				curr = head;
			}
			else
			{
				curr = head;
				while (1)
				{
					if (data < curr->data)
					{
						newnode->prev = curr->prev;
						newnode->next = curr;
						curr->prev->next = newnode;
						curr->prev = newnode;
						if (curr == head)
							head = newnode;
						break;
					}
					else if (data == curr->data)
						break;
					else
					{
						if (curr->next == head)
						{
							newnode->prev = curr;
							newnode->next = curr->next;
							curr->next->prev = newnode;
							curr->next = newnode;
						}
						else
							curr = curr->next;
					}
				}
			}
		}
		else if (!strcmp(command, "DELETE"))
		{
			int data;
			fscanf(input, "%d", &data);
			listPointer delnode;
			if (head != NULL)
			{
				curr = head;
				while (1)
				{
					if (data == curr->data)
					{
						delnode = curr;
						if (delnode == head)
						{
							if (curr->next == head)
							{
								free(head);
								head = NULL;
								break;
							}
							else
								head = head->next;
						}
						delnode->next->prev = delnode->prev;
						delnode->prev->next = delnode->next;
						free(delnode);
						break;
					}
					curr = curr->next;
					if (curr == head)
						break;
				}
			}
		}
		else if (!strcmp(command, "ASCEND"))
			print_forward(head);
		else if (!strcmp(command, "DESCEND"))
			print_reverse(head);
		else
			break;
	}
	fclose(input);
	fclose(result);

	if (head != NULL)
	{
		head->prev->next = NULL;
		curr = head;
		while (curr != NULL)
		{
			curr->prev = NULL;
			head = curr->next;
			free(curr);
			curr = head;
		}
	}
	return 0;
}

void print_forward(listPointer list) {
	listPointer curr;
	FILE* outfile;
	outfile = fopen("hw2_result.txt", "a");
	if (list) {
		curr = list;
		while (1) {
			fprintf(outfile, "%d ", curr->data);
			printf("%d ", curr->data);
			curr = curr->next;
			if (curr == list) break;
		}
	}
	fprintf(outfile, "\n");
	printf("\n");
	fclose(outfile);
}

void print_reverse(listPointer list) {
	listPointer curr;
	FILE* outfile;
	outfile = fopen("hw2_result.txt", "a");
	if (list) {
		curr = list->prev;
		while (curr != list) {
			fprintf(outfile, "%d ", curr->data);
			printf("%d ", curr->data);
			curr = curr->prev;
		}
		fprintf(outfile, "%d ", curr->data);
		printf("%d ", curr->data);
	}
	fprintf(outfile, "\n");
	printf("\n");
	fclose(outfile);
}