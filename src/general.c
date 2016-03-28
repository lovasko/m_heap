#include "m_heap.h"

int
m_heap_init(m_heap* heap,
            size_t obj_size,
            size_t d,
            int(*cmp_fn)(const void*,const void*))
{
	int ret;

	if (heap == NULL || cmp_fn == NULL)
		return M_HEAP_E_NULL;
	
	if (obj_size == 0)
		return M_HEAP_E_SIZE;

	if (d < 2)
		return M_HEAP_E_D;

	heap->obj_size = obj_size;
	heap->d = d;
	heap->cmp_fn = cmp_fn;

	ret = m_array_init(&heap->array, d*d+1, obj_size);
	if (ret != M_ARRAY_OK)
		return ret;

	return M_HEAP_OK;
}

int
m_heap_free(m_heap* heap)
{
	int ret; 

	if (heap == NULL)
		return M_HEAP_E_NULL;

	ret = m_array_free(&heap->array);
	if (ret != M_ARRAY_OK)
		return ret;

	return M_HEAP_OK;
}

int
m_heap_trim(m_heap* heap)
{
	int ret;

	if (heap == NULL)
		return M_HEAP_E_NULL;

	ret = m_array_trim(&heap->array);
	if (ret != M_ARRAY_OK)
		return ret;

	return M_HEAP_OK;
}

