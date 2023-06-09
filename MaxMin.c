#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
/*shira giladi and pessy*/
/*print the heap*/
void print_heap(int * heap);
/*Finding the depth of the tree*/
int find_depth(int i);
/*Deleting a node from the stack. So the stack will remain a max-min stack*/
void heap_delete(int * heap, int index);
/*finding the parent from heap*/
int parent(int * heap, int i);
/*Finding the maximum node from the stack*/
int find_max(int * heap);
/*Finding the minimum node from the stack*/
int find_min(int * heap);
/*A helper function that helps find the left child in the stack by getting the index of the father*/
int left_child(int * heap, int i);
/*A helper function that helps find the right child in the stack by getting the index of the father*/
int right_child(int * heap, int i);
/*An auxiliary function that switches between 2 spark plugs in a stack*/
void swap(int * heap, int i, int max);
/*heapify function from which 2 functions were sent, heapify max, heapify min*/
void heapify(int * heap, int i);
/*A helper function that finds the smallest node among the node's child or grandchild*/
int find_min_child_grandchild(int * heap, int i);
/*A helper function that finds the biggest node among the node's child or grandchild*/
int find_max_child_grandchild(int * heap, int i);
/*Helper function that heapify all nodes that are of even depth*/
void heapify_max(int * heap, int i);
/*Helper function that heapifies all nodes that are of odd depth*/
void heapify_min(int * heap, int i);
/*A function that builds the max-min stack*/
void build_heap(int * heap);
/*A function that extracts the maximum from the stack by saving the nax-min stack properties*/
void heap_extract_max(int * heap);
/*A function that extracts the minimum from the stack by saving the nax-min stack properties*/
void heap_extract_min(int * heap);
/*A function that inserts a member into the stack by saving the max-min stack properties*/
void heap_insert(int *heap, int key);
/*A function that sorts the max-min stack*/
void heap_sort(int * heap);
/*A global variable that holds the size of the stack*/
int heap_size;

/*The main function asks the user to insert the members of the stack, then it prints the user's choice, and gives the user the option to choose which action he wants from the menu on the stack.*/
int main()
{
	int todo;
	int index;
	int key;
	int heap[512];/*It was announced in the forum that a maximum size can be assigned to the heap.*//* = {45,33,55,15,28,66,64,18,14,49};*/
	int i = 0;
	int j;
	int count = 0;
	printf("Please enter numbers separated by spaces:\n");
	while (i < 512 && scanf("%d", &heap[i]) == 1)
	{
      		i++;
   	}
   	printf("\nThe numbers you entered are:\n");

	for (j = 0; j < i; j++) 
	{
	      printf("%d ", heap[j]);
	      count = count+1;
	}
	printf("\n");
	heap_size = count;
	printf("To build heap press 1,\n (for exit press 0)\n");
	scanf("%d", &todo);
	switch(todo)
	{
		case 1:
			build_heap(heap);
			break;
		case 0:
			exit(0);
	}
	while(todo != 0)
	{
		printf("\n2 - find max\n3 - find min\n4 - extraxt max\n5 - extract min\n6 - insert to heap\n7 -  delete from heap\n8 - sort heap\n9 - print heap\n(0 - exit)\n");
		scanf("%d", &todo);
		switch(todo)
		{
			case 2:
				find_max(heap);
				break;
			case 3:
				find_min(heap);
				break;
			case 4:
				heap_extract_max(heap);
				break;
			case 5:
				heap_extract_min(heap);
				break;
			case 6:
				printf("Enter the value of number to insert:\n");
			 	scanf("%d",&key);
				heap_insert(heap,key);
				break;
			case 7:
				printf("Enter the index of number to delete:\n");
				scanf("%d", &index);
				heap_delete(heap, index);
				break;
			case 8:
				heap_sort(heap);
				break;
			case 9:
				print_heap(heap);
				break;
				
			case 0:
				exit(0);
		}
	}
	return 0;
}

/*A function that finds the maximum member that must necessarily be at the root of the max-min stack*/
int find_max(int * heap)
{
	printf("Max number: %d\n", heap[0]);
	return heap[0];
}

/*A function that finds the minimum member that must necessarily be in one of the members of the root of the tree (the stack)*/
int find_min(int * heap)
{
	if(heap[1] < heap[2])
	{
		printf("Min number: %d\n", heap[1]);
		return heap[1];
	}
	printf("Min number: %d\n", heap[2]);
	return heap[2];
}
/*A function that receives an index of a node and the stack and finds the left child of that root from the stack*/
int left_child(int * heap, int i)
{
	if(heap_size < 2*i+2)
		return -1;
	return 2*i+1;
}

/*A function that receives an index of a node and the stack and finds the right child of that root from the stack*/
int right_child(int * heap, int i)
{
	if(heap_size < 2*i+3)
		return -1;
	return 2*i+2;
}

/*A function that receives an index of a node and the stack and finds the parent of that root from the stack*/
int parent(int * heap, int i)
{
	return (i-1)/2;
}

/*A function that accepts a stack and builds a stack by max_min stack properties*/
void build_heap(int * heap)
{
	int i;
	for (i = heap_size/2-1; i>=0; i--)
	{
		heapify(heap, i);
	}
	print_heap(heap);
}

/*A function that receives an index of a node in the heap and sends respectively (of the heap attributes) to the heapify_min and heapify_max functions. In such a way that for every node with an even depth we send to heapify_min and every node with an odd depth is sent to heapify_max*/
void heapify(int * heap, int i)
{
	int dep = find_depth(i);
	if((dep % 2) == 0)
	{
		heapify_max(heap, i);
	}
	else
	{
		heapify_min(heap, i);
	}
}

/*A helper function that accepts an index and finds the depth of the index. In order to understand if the node of that index is at an odd depth or at an even depth*/
int find_depth(int i)
{
	int dep = 0;
	while(i > 0)
	{
		i = (i - 1) / 2;
		dep++;
	}
	return dep;
}

/*A helper function pushes down respectively all the indexes that are in an even depth*/
void heapify_max(int * heap, int i)
{
	int max_index;
	if(heap_size < 2*i + 1)
	{
		return;
	}
	max_index  = find_max_child_grandchild(heap, i);
	if(max_index == 2*i+1 || max_index == 2*i+2)/*if is child*/
	{
		if(heap[max_index] > heap[i])
		{
			swap(heap, i, max_index);
		}
	}
	else
	{
		if(heap[max_index] > heap[i])
		{
			swap(heap, i, max_index);
			if(heap[max_index] < heap[(max_index-1)/2])
			{
				swap(heap, (max_index-1)/2, max_index);
			}
			heapify(heap, max_index);
		}
	}
}

/*A helper function pushes down respectively all the indexes that are in an odd depth*/
void heapify_min(int * heap, int i)
{
	int min_index;
	if(heap_size < 2*i+1)
	{
		return;
	}
	min_index = find_min_child_grandchild(heap, i);
	if(min_index == 2*i+1 || min_index == 2*i+2)/*if is child*/
	{
		if(heap[min_index] < heap[i])
		{
			swap(heap, i, min_index);
		}
	}
	else
	{
		if(heap[min_index] < heap[i])
		{
			swap(heap, i, min_index);
			if(heap[min_index] > heap[(min_index-1)/2])
			{
				swap(heap, (min_index-1)/2, min_index);
			}
			heapify(heap, min_index);
		}
	}
}

/*A helper function that accepts the list random index and index of max, and replaces them.*/
void swap(int * heap, int i, int max)
{
	int temp = heap[i];
	heap[i] = heap[max];
	heap[max] = temp;
}

/*A helper function that accepts the list and a random index and returns the largest child/grandchild that node has at the particular index*/	
int find_max_child_grandchild(int * heap, int i)
{
	int left = left_child(heap, i);
	int right = right_child(heap, i);
	int left_left= left_child(heap, left_child(heap, i));
	int left_right= right_child(heap, left_child(heap, i));
	int right_left= left_child(heap, right_child(heap, i));
	int right_right= right_child(heap, right_child(heap, i));
	int max = heap[i];
	int max_index = i;
	if(left > 0 && max < heap[left])
	{
		max = heap[left];
		max_index = left;
	}
	if(right > 0 && max < heap[right])
	{
		max = heap[right];
		max_index = right;
	}
	if(left_left > 0 && max < heap[left_left])
	{
		max = heap[left_left];
		max_index = left_left;
	}
	if(left_right > 0 && max < heap[left_right])
	{
		max = heap[left_right];
		max_index = left_right;
	}
	if(right_left > 0 && max < heap[right_left])
	{
		max = heap[right_left];
		max_index = right_left;
	}
	if(right_right > 0 && max < heap[right_right])
	{
		max = heap[right_right];
		max_index = right_right;
	}
	return max_index;
}

/*A helper function that accepts the list and a random index and returns the smallest child/grandchild that node has at the particular index*/		
int find_min_child_grandchild(int * heap, int i)
{
	int left = left_child(heap, i);
	int right = right_child(heap, i);
	int left_left= left_child(heap, left_child(heap, i));
	int left_right= right_child(heap, left_child(heap, i));
	int right_left= left_child(heap, right_child(heap, i));
	int right_right= right_child(heap, right_child(heap, i));
	int min = heap[i];
	int min_index = i;
	if(left > 0 && min > heap[left])
	{
		min = heap[left];
		min_index = left;
	}
	if(right > 0 && min > heap[right])
	{
		min = heap[right];
		min_index = right;
	}
	if(left_left > 0 && min > heap[left_left])
	{
		min = heap[left_left];
		min_index = left_left;
	}
	if(left_right > 0 && min > heap[left_right])
	{
		min = heap[left_right];
		min_index = left_right;
	}
	if(right_left > 0 && min > heap[right_left])
	{
		min = heap[right_left];
		min_index = right_left;
	}
	if(right_right > 0 && min > heap[right_right])
	{
		min = heap[right_right];
		min_index = right_right;
	}
	return min_index;
}

/*A function that prints the stack visibility after each action the user chooses to perform.*/
void print_heap(int * heap)
{
	int i;
	for(i = 0; i < heap_size; i++)
	{
		printf("%d\t", heap[i]);
	}
	printf("\n");
}

/*A function that extracts the maximum member by keeping the max_min heap properties and of course not forgetting to lower the number of heap indexes by 1*/
void heap_extract_max(int * heap)
{
	heap[0] = heap[heap_size-1];
	heap_size--;
	heapify(heap, 0);
	print_heap(heap);
}

/*A function that extracts the minimum member by keeping the max_min heap properties and of course not forgetting to lower the number of heap indexes by 1*/
void heap_extract_min(int * heap)
{
	int min_index = 1;
	if(heap[2] < heap[1])
	{
		min_index = 2;
	}
	heap[min_index] = heap[heap_size-1];
	heap_size--;
	heapify(heap, min_index);
	print_heap(heap);
}

/*A function that receives the stack and index and deletes an element from the list by saving the max-min stack attributes*/
void heap_delete(int * heap, int index)
{
	heap[index] = heap[heap_size-1];
	heap_size--;
	heapify(heap, index);
	print_heap(heap);
}

/*A function that receives a key-value and the stack, the function takes care of inserting the value in its appropriate place in such a way that the stack remains a max-min stack*/
void heap_insert(int *heap, int key) 
{
    int i;
    heap_size = heap_size+1;
    i = heap_size-1;
    heap[i] = key;
    build_heap(heap);
}

/*A function that receives the stack and sorts its members from largest to smallest*/
void heap_sort(int * heap)
{
	int i;
	int temp = heap_size;
	for(i = heap_size-1; i >= 1; i--)
	{
		swap(heap, i, 0);
		heap_size--;
		heapify(heap, 0);
	}
	heap_size=temp;
	print_heap(heap);
	exit(0);
}
