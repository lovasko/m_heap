#ifndef M_HEAP_H
#define M_HEAP_H

#include <stddef.h>
#include <m_array.h>

#define M_HEAP_OK     0
#define M_HEAP_E_NULL 1
#define M_HEAP_E_D    2
#define M_HEAP_E_SIZE 3

typedef struct m_heap {
	struct m_array array;
	size_t obj_size;
	size_t d;
	int(*cmp_fn)(const void*,const void*);
} m_heap;

int m_heap_init(m_heap* heap, size_t obj_size, size_t d, int(*cmp_fn)(const void*,const void*));
int m_heap_free(m_heap* heap);
int m_heap_trim(m_heap* heap);
int m_heap_push(m_heap* heap, void* object);
int m_heap_peek(m_heap* heap, void** out_object);
int m_heap_pop(m_heap* heap);

#endif

