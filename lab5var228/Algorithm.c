#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Algorithm.h"
  // Function to swap the the position of two elements
  void swap(void *a, void *b, size_t size) {
    char* temp = malloc(size);
    memcpy((void*)temp, a, size);
    // printf("%d\n", sizeof(char));
    memcpy(a, b, size);
    memcpy(b, (void*)temp, size);
  }
  
  void heapify(void* arr, int n, int i, int size, cmp_t cmp) {
    // Find largest among root, left child and right child
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
  
    if (left < n && cmp((void*)((char*)arr + left * size), (void*)((char*)arr + largest* size)) == 1)
      largest = left;
  
    if (right < n && cmp((void*)((char*)arr + right* size), (void*)((char*)arr + largest* size)) == 1)
      largest = right;
  
    // Swap and continue heapifying if root is not largest
    if (largest != i) {
      swap((void*)((char*)arr + i* size), (void*)((char*)arr + largest* size), size);
      heapify(arr, n, largest, size, cmp);
    }
  }
  
  // Main function to do heap sort
  void heapSort(void* arr, int n, int size, cmp_t cmp) {
    // Build max heap
    for (int i = n / 2 - 1; i >= 0; i--)
      heapify(arr, n, i, size, cmp);
  
    // Heap sort
    for (int i = n - 1; i >= 0; i--) {
      swap(arr, (void*)((char*)arr + i* size), size);
  
      // Heapify root element to get highest element at root again
      heapify(arr, i, 0, size, cmp);
    }
  }
  
  