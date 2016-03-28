#!/bin/sh

INC_DIR=/usr/include
LIB_DIR=/usr/lib

cp -v bin/libmheap.so "${LIB_DIR}"
cp -v src/m_heap.h "${INC_DIR}"

