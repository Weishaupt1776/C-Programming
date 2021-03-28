#include <stdio.h>
#include <stdlib.h>
 
typedef struct _queue
{
	int capacity[10];
	int front;
	int size;
}queue;

void initialize_queue(queue* sequence)
{
	sequence->front = 0;
	sequence->size = 0;
}

int enqueue(queue* sequence, int value) // Fix this
{	
	static int dequeued_index = 0;	
	if(sequence->size == 10) // If queue capacity has been met
	{
		if(sequence->front == 0) // If queue capacity is met and no element has been dequeued, terminate program
		{
			printf("Error: cannot enqueue, storage capacity met\n");
			return -1;
		}
		else if(sequence->front != 0) // If element has been dequeued
		{
			if(dequeued_index < sequence->front)
			{
				sequence->capacity[dequeued_index] = value;
				dequeued_index++;
				return 1;
			}
			else if(dequeued_index == sequence->front)
			{
				printf("Error: cannot enqueue, storage capacity met\n");
				return -1;
			}
		}
	}
	else if(sequence->size < 10)
	{
		sequence->capacity[sequence->size] = value;
		sequence->size++;
		return 1;
	}
	return 1;
}

int dequeue(queue* sequence)
{
	if(sequence->front >= 10)
	{
		printf("Error: cannot dequeue, out of bounds index encountered\n");
		return -1;
	}
	else
	{
		sequence->front++;
		return 1;
	}
}

void print_queue(queue* sequence)
{
	int queue_index;
	for(queue_index = sequence->front; queue_index < sequence->size; queue_index++)
	{
		printf("%i ", sequence->capacity[queue_index]);
	}
	putchar('\n');
}

typedef struct _stack
{
	int pile[10];
	int top;
}stack;

void initialize_stack(stack* heap)
{
	heap->top = 0;
}

int push(stack* heap, int value)
{
	if(heap->top == 10)
	{
		printf("Error: stack limit has been met and further pushing will exceed space allocated\n");
		return -1;
	}
	else
	{
		heap->pile[heap->top] = value; // adds new value to top of stack
		heap->top++; // moves top of stack to next index
		return 1;
	}	
}

void pop(stack* heap)
{
	heap->top--;
}

void print_stack(stack* heap)
{
	int stack_index;
	for(stack_index = heap->top - 1; stack_index >= 0; stack_index--)
	{
		printf("%i\n", heap->pile[stack_index]);
	}
}

typedef struct sllist
{
	int value;
	struct sllist* next;
}sllnode;

sllnode* initialize_sllist(sllnode* head, int num_of_nodes)
{
	for(int i = 0; i < num_of_nodes; i++)
	{
		sllnode* node = (sllnode*)malloc(sizeof(sllnode));
		node->value = 0;
		node->next = head;
		head = node;
	}
	return head;
}

sllnode* insert_sllnode(sllnode* head, int new_value)
{
	sllnode* node = (sllnode*)malloc(sizeof(sllnode));
	node->value = new_value;
	node->next = head;
	head = node;
	return head;
}

sllnode* delete_sllnode(sllnode* head, int node_to_be_deleted)
{
	if(head->value == node_to_be_deleted) // Checks if this first node is the one which the programmer intends to delete
	{
		head = head->next;
		return head;
	}
	else // If first node was not the intended node to delete, iterate through linked list until desired node is encountered
	{
		sllnode* traversal = head;
		sllnode* link = head;
		while(traversal != NULL)
		{
			if(traversal->value == node_to_be_deleted && traversal->next != NULL)
			{
				while(link->next != traversal)
				{
					link = link->next;
				}
				traversal = traversal->next;
				link->next = traversal;
			}
			else if(traversal->value == node_to_be_deleted && traversal->next == NULL)
			{
				while(link->next != traversal)
				{
					link = link->next;
			  	}
				link->next = NULL;
				return head;
			}
			else if(traversal->value != node_to_be_deleted)
			{
				traversal = traversal->next;
			}
		}
	}
		return head;
}

sllnode* search_sllist(sllnode* head, int element_sought)
{
	sllnode* seeker = head;
	while(seeker != NULL)
	{
		if(seeker->value == element_sought)
			return seeker;
		else
			seeker = seeker->next;
	}
	printf("Element not found in linked-list\n");
	return head;
}

void delete_sllist(sllnode* head)
{
	sllnode* list = head;
	if(list->next != NULL)
		delete_sllist(list->next);
	free(list);
}

void print_sllist(sllnode* head)
{
	sllnode* traversal = head;
	if(traversal == NULL)
		printf("Error\n");
	else
	{
		while(traversal->next != NULL)
		{
			printf(" %i ", traversal->value);
			traversal = traversal->next;
			if(traversal->next != NULL)
			{
				printf("->");
			}
			else
				printf("-> %i ", traversal->value);
		}
		putchar('\n');
	}
	printf("End\n");
}

typedef struct _dllist
{
	int value;
	struct _dllist* prev;
	struct _dllist* next;
}dllnode;

dllnode* initialize_dllist(dllnode* head, int num_of_nodes)
{
	dllnode* initial_node = (dllnode*)malloc(sizeof(dllnode));
	initial_node->prev = NULL;
	initial_node->next = NULL;
	head = initial_node;
	for(int i = 0; i < num_of_nodes - 1; i++)
	{
		dllnode* new_node = (dllnode*)malloc(sizeof(dllnode));
		new_node->prev = head;
		head->next = new_node;
		head = new_node;
		new_node->value = 0;
		new_node->next = NULL;
	}
	while(head->prev != NULL)
		head = head->prev;
	return head;
}
 
 dllnode* insert_dllnode(dllnode* head, int value)
 {
	 dllnode* new_node = (dllnode*)malloc(sizeof(dllnode));
	 new_node->prev = NULL;
	 new_node->value = value;
	 new_node->next = head;
	 head->prev = new_node;
	 head = new_node;
	 return head;
 }
 
 dllnode* delete_dllnode(dllnode* head, int element_to_be_deleted)
 {
	 dllnode* traversal = head;
	 if(traversal->value == element_to_be_deleted)
	 {
		 traversal = traversal->next;
		 head = head->next;
		 return head;
	 }
	 else if(traversal->value != element_to_be_deleted)
	 {
		 traversal = traversal->next;
		 while(traversal->value != element_to_be_deleted && traversal->next != NULL)
			 traversal = traversal->next;
	 }
	 if(traversal->value == element_to_be_deleted)
	 {
		 if(traversal->value == element_to_be_deleted && traversal->next == NULL)
		 {
			 traversal = traversal->prev;
			 traversal->next = NULL;
			 return head;
		 }
		 else if(traversal->value == element_to_be_deleted && traversal->next != NULL)
		 {
			 dllnode* link = traversal;
			 traversal = traversal->prev;
			 traversal->next = link->next;
			 traversal = link->next;
			 traversal->prev = link->prev;
			 link = NULL;
			 return head;
		 }
	 }
	 else
	 {
		 printf("Element was not found in linked list\n");
	 }
	 return head;
	
 }
 
 dllnode* delete_dllist(dllnode* head)
 {
	 dllnode* traversal = (dllnode*)malloc(sizeof(traversal));
	 traversal = head;
	 while(head != NULL)
	 {
		 head = head->next;
		 free(traversal);
		 traversal = head;
	 }
	 return head;
 }
 
 dllnode* search_dllist(dllnode* head, int element)
 {
	 dllnode* traversal = head;
	 while(traversal != NULL || traversal->value != element)
		 traversal = traversal->next;
	 if(traversal-> value == element)
	 {
		 printf("Element found!\n");
		 return traversal;
	 }
	 else
	 {
		 printf("Element not in linked-list\n");
		 return head;
	 }
 }
 
 void print_dllist_info(dllnode* head)
 {
	 dllnode* index = head;
	 int count = 1;
	 while(index != NULL)
	 {
		 printf("The address of dllnode %i is %p\n", count, (void*)&index);
		 printf("The address of dllnode->prev is %p\n", (void*)&index->prev);
		 printf("The address of dllnode->next is %p\n", (void*)&index->next);
		 putchar('\n');
		 index = index->next;
		 count++;
	 }
 }
 
void print_dllist(dllnode* head)
{
	dllnode* traversal = head;
	if(traversal == NULL)
		printf("No linked-list found\n");
	else if(traversal != NULL)
	{
		while(traversal != NULL)
		{
			printf("%i --- ", traversal->value);
			traversal = traversal->next;
		}
	}
}
