#ifndef __ARRAY_H
#define __ARRAY_H

#include <stdio.h>

#define EYEMENT_TYPE void *
typedef struct Array {

  size_t size;

  size_t capacity;

  EYEMENT_TYPE *data;
} verctor;

int ArrayInit(verctor *arr, size_t capacity);

int ArrayInsert(verctor *arr, size_t index, EYEMENT_TYPE value);

int ArrayInsertEnd(verctor *arr, EYEMENT_TYPE value);

int ArrayGetSize(verctor *arr, int *pSize);

int ArrayGetCapacity(verctor *arr, int *pCapacity);

int ArrayDelete(verctor *arr, size_t index);

int ArrayDeleteEnd(verctor *arr);

int ArrayDestory(verctor *arr);

#endif
