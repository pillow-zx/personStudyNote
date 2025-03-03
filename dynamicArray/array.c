#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum STATUS {
  ON_SUCCESS,
  NULL_PTR,
  MALLO_ERROR,
  ACCESS_ERROR,
};

#define DEFAULT_CAPACITY 10

static int expanArrayCapacity(verctor *arr);
static int shrinkArrayCapacity(verctor *arr);

int ArrayInit(verctor *arr, size_t capacity) {
  if (arr == NULL) {
    perror("arr is NULL: ");
    return NULL_PTR;
  }

  if (capacity == 0) {
    capacity = DEFAULT_CAPACITY;
  }

  arr->data = (EYEMENT_TYPE *)malloc(sizeof(EYEMENT_TYPE) * capacity);
  if (arr->data == NULL) {
    perror("mallloc failed:");
    return MALLO_ERROR;
  }

  memset(arr->data, 0, sizeof(EYEMENT_TYPE) * capacity);

  arr->size = 0;
  arr->capacity = capacity;

  return ON_SUCCESS;
}

int ArrayInsert(verctor *arr, size_t index, EYEMENT_TYPE value) {
  if (arr == NULL) {
    perror("array is NULL: ");
    return NULL_PTR;
  }

  if (index < 0 || index > arr->size) {
    perror("index is out of range: ");
    return ACCESS_ERROR;
  }

  if (arr->size >= arr->capacity) {
    expanArrayCapacity(arr);
  }

  for (int idx = arr->size; idx > index; idx--) {
    arr->data[idx] = arr->data[idx - 1];
  }

  arr->data[index] = value;
  (arr->size)++;

  return ON_SUCCESS;
}

int ArrayInsertEnd(verctor *arr, EYEMENT_TYPE value) {
  return ArrayInsert(arr, arr->size, value);
}

int ArrayGetSize(verctor *arr, int *pSize) {
  if (arr == NULL || pSize == NULL) {
    perror("array or pSize is NULL: ");
    return NULL_PTR;
  }

  *pSize = arr->size;

  return ON_SUCCESS;
}

int ArrayGetCapacity(verctor *arr, int *pCapacity) {
  if (arr == NULL || pCapacity == NULL) {
    perror("array or pCapacity is NULL: ");
    return NULL_PTR;
  }

  *pCapacity = arr->capacity;

  return ON_SUCCESS;
}

int ArrayDelete(verctor *arr, size_t index) {
  if (arr == NULL) {
    perror("array is NULL: ");
    return NULL_PTR;
  }

  if (index < 0 || index >= arr->size) {
    perror("index is out of range: ");
    return ACCESS_ERROR;
  }

  if (arr->size <= arr->capacity >> 1) {
    shrinkArrayCapacity(arr);
  }

  for (int idx = index; idx < arr->size - 1; idx++) {
    arr->data[idx] = arr->data[idx + 1];
  }

  (arr->size)--;

  return ON_SUCCESS;
}

int ArrayDeleteEnd(verctor *arr) { return ArrayDelete(arr, arr->size - 1); }

int ArrayDestory(verctor *arr) {
  if (arr == NULL) {
    perror("array is NULL: ");
    return NULL_PTR;
  }

  if (arr->data != NULL) {
    free(arr->data);
    arr->data = NULL;
  }

  arr->size = 0;
  arr->capacity = 0;

  return ON_SUCCESS;
}

static int expanArrayCapacity(verctor *arr) {
  int ret = 0;

  EYEMENT_TYPE *tempdata = arr->data;

  arr->data = (EYEMENT_TYPE *)malloc(sizeof(EYEMENT_TYPE) * arr->capacity * 2);
  if (arr->data == NULL) {
    perror("mallloc failed:");
    arr->data = tempdata;
    return MALLO_ERROR;
  }
  memset(arr->data, 0, sizeof(EYEMENT_TYPE) * arr->capacity * 2);

  for (int idx = 0; idx < arr->size; idx++) {
    arr->data[idx] = tempdata[idx];
  }

  if (tempdata != NULL) {
    free(tempdata);
    tempdata = NULL;
  }

  arr->capacity *= 2;

  return ON_SUCCESS;
}

static int shrinkArrayCapacity(verctor *arr) {
  EYEMENT_TYPE *tempdata = arr->data;

  arr->data = (EYEMENT_TYPE *)malloc(sizeof(EYEMENT_TYPE) * arr->capacity >> 1);
  if (arr->data == NULL) {
    perror("mallloc failed:");
    arr->data = tempdata;
    return MALLO_ERROR;
  }

  memset(arr->data, 0, sizeof(EYEMENT_TYPE) * arr->capacity >> 1);

  for (int idx = 0; idx < arr->size; idx++) {
    arr->data[idx] = tempdata[idx];
  }

  if (tempdata != NULL) {
    free(tempdata);
    tempdata = NULL;
  }

  arr->capacity >>= 1;

  return ON_SUCCESS;
}
