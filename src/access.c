#include "m_heap.h"

int
m_heap_push(m_heap* heap, void* object)
{
	size_t idx;
	size_t parent_idx;
	void* o;
	void* p;

	if (heap == NULL || object == NULL)
		return M_HEAP_E_NULL;

	m_array_append(&heap->array, 1, object);
	m_array_length(&heap->array, &idx);

	while (idx != 0) {
		parent_idx = (idx-1)/heap->d;
		m_array_get(&heap->array, idx, (void**)&o);
		m_array_get(&heap->array, parent_idx, (void**)&p);
		if (heap->cmp_fn(o, p) >= 0)
			break;

		m_array_swap(&heap->array, idx, parent_idx, 1);
		idx = parent_idx;
	}

	return M_HEAP_OK;
}

int
m_heap_peek(m_heap* heap, void** out_object)
{
	int ret;

	if (heap == NULL || out_object == NULL)
		return M_HEAP_E_NULL;
	
	ret = m_array_get(&heap->array, 0, out_object);
	if (ret != M_ARRAY_OK)
		return ret;

	return M_HEAP_OK;
}

int
m_heap_pop(m_heap* heap)
{
	size_t length;
	size_t idx;
	size_t min;
	size_t start;
	size_t end;

	if (heap == NULL)
		return M_HEAP_E_NULL;

	m_array_length(&heap->array, &length);
	m_array_swap(&heap->array, 0, length-1, 1);
	m_array_remove_last(&heap->array, 1);
	m_array_length(&heap->array, &length);

	idx = 0;
	while (1) {
		start = idx * heap->d + 1;
		end = idx * heap->d + heap->d;

		if (start >= length)
			break;

		if (end >= length)
			end = length-1;

		m_array_extremes(&heap->array, start, end, heap->cmp_fn, &min, NULL);
		m_array_swap(&heap->array, idx, min, 1);
		idx = min;
	}

	return M_HEAP_OK;
}

