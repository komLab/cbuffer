#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BUFFER_SIZE 1024

typedef struct {
	uint32_t value[2];
}reading;

typedef struct {
	int size;
	int head;
	int tail;
	reading *addr;
}cbuffer;


int alloc_buffer(cbuffer *buffer, int size)
{
	buffer->addr = malloc(size * sizeof(reading));
	if(buffer->addr == NULL) {
		printf("Can't allocate virtual memory.\n");
		return 1;
	}

	buffer->size = size + 1;
	buffer->head = 0;
	buffer->tail = 0;

	printf("allocate virtual memory. CHECK!\n");
	return 0;
}

int free_buffer(cbuffer *buffer)
{
	if (buffer->addr == NULL) {
		printf("Can't free virtual memory.\n");
		return 1;
	}

	free(buffer->addr);
	printf("free virtual memory. CHECK!\n");

	return 0;
}

void add_buffer(cbuffer *buffer, reading *element)
{
	buffer->addr[buffer->tail] = *element;
	buffer->tail = (buffer->tail + 1) % buffer->size;
	if (buffer->tail == buffer->head)
		buffer->head = (buffer->head + 1) % buffer->size;
}

void pop_buffer(cbuffer *buffer, reading *element)
{
	*element = buffer->addr[buffer->head];
	buffer->head = (buffer->head + 1) % buffer->size;
}

int main(void)
{
	int i;
	reading temp;
	cbuffer my_buffer;

	if(alloc_buffer(&my_buffer, BUFFER_SIZE) == 1)
		return EXIT_FAILURE;

	for (i = 0; i < BUFFER_SIZE; i++) {
		temp.value[0] = i;
		temp.value[1] = BUFFER_SIZE - i -1;
		add_buffer(&my_buffer, &temp);
	}
	for (i = 0; i < BUFFER_SIZE; i++) {
		pop_buffer(&my_buffer, &temp);
		printf("%d,%d\n", temp.value[0], temp.value[1]);
	}

	if(free_buffer(&my_buffer) == 1)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}
