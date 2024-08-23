#include <stdio.h>
#include <stdlib.h>

// Min heap structure for priority queue
typedef struct {
    long long *data;
    int size;
    int capacity;
} MinHeap;

// Function to initialize a MinHeap
MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->data = (long long*)malloc(sizeof(long long) * capacity);
    minHeap->size = 0;
    minHeap->capacity = capacity;
    return minHeap;
}

// Function to swap two elements in the heap
void swap(long long* x, long long* y) {
    long long temp = *x;
    *x = *y;
    *y = temp;
}

// Function to heapify down the heap
void heapifyDown(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->data[left] < minHeap->data[smallest])
        smallest = left;

    if (right < minHeap->size && minHeap->data[right] < minHeap->data[smallest])
        smallest = right;

    if (smallest != idx) {
        swap(&minHeap->data[idx], &minHeap->data[smallest]);
        heapifyDown(minHeap, smallest);
    }
}

// Function to heapify up the heap
void heapifyUp(MinHeap* minHeap, int idx) {
    int parent = (idx - 1) / 2;

    if (idx && minHeap->data[idx] < minHeap->data[parent]) {
        swap(&minHeap->data[idx], &minHeap->data[parent]);
        heapifyUp(minHeap, parent);
    }
}

// Function to extract the minimum element from the heap
long long extractMin(MinHeap* minHeap) {
    if (minHeap->size == 0)
        return -1;

    long long root = minHeap->data[0];

    if (minHeap->size > 1) {
        minHeap->data[0] = minHeap->data[minHeap->size - 1];
        heapifyDown(minHeap, 0);
    }

    minHeap->size--;
    return root;
}

// Function to insert an element into the heap
void insertMinHeap(MinHeap* minHeap, long long val) {
    if (minHeap->size == minHeap->capacity) {
        minHeap->capacity *= 2;
        minHeap->data = (long long*)realloc(minHeap->data, sizeof(long long) * minHeap->capacity);
    }

    minHeap->size++;
    minHeap->data[minHeap->size - 1] = val;
    heapifyUp(minHeap, minHeap->size - 1);
}

// Function to calculate nth regular number
long long nthRegularNumber(int n) {
    int primes[3] = {2, 3, 5};
    MinHeap* heap = createMinHeap(100);
    insertMinHeap(heap, 1);

    long long regularNumber = 1;
    for (int i = 1; i <= n; i++) {
        regularNumber = extractMin(heap);
        // Avoid duplicates by skipping numbers already in the heap
        while (heap->size > 0 && heap->data[0] == regularNumber) {
            extractMin(heap);
        }
        // Insert next possible regular numbers
        for (int j = 0; j < 3; j++) {
            insertMinHeap(heap, regularNumber * primes[j]);
        }
    }

    free(heap->data);
    free(heap);
    return regularNumber;
}

int main() {
    int n = 1500;
    for (int i = 1; i <= 10; i++) {
        /*should be 1, 2, 3, 4, 5, 6, 8, 9, 10, 12*/
        printf("The %dth regular number is %lld\n", i, nthRegularNumber(i));
    }
    // ?
    printf("The %dth regular number is %lld\n", n, nthRegularNumber(n));
    return 0;
}
