#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <m_heap.h>

static int
cmp_uint16_t(const void* a, const void* b)
{
	return (*(uint16_t*)a - *(uint16_t*)b);
}

int
main(void)
{
	int dev_random;
	m_heap heap;
	uint16_t number;
	uint16_t* out;
	unsigned int i;

	dev_random = open("/dev/random", O_RDONLY);
	m_heap_init(&heap, sizeof(uint16_t), 3, cmp_uint16_t);

	for (i = 0; i < 100; i++) {
		read(dev_random, &number, sizeof(uint16_t));
		m_heap_push(&heap, &number);
	}
	close(dev_random);

	for (i = 0; i < 100; i++) {
		m_heap_peek(&heap, (void**)&out);
		printf("%u ", *out);
		m_heap_pop(&heap);
	}
	printf("\n");

	m_heap_free(&heap);
	return EXIT_SUCCESS;
}

