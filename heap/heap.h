/*
 * heap
 */

#ifndef HEAP_H
#define HEAP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Move array[index] upward in a min-heap; invalid inputs are ignored. */
void upAdjust(int array[], int length, int index);
/*
 * Restore a min-heap by moving array[index] downward. The subtrees rooted at
 * index's children must already be min-heaps. A null array, non-positive
 * lengths, and indexes outside [0, length) are ignored.
 */
void downAdjust(int array[], int length, int index);
/* Build a min-heap in place; null arrays and lengths below two are no-ops. */
void buildHeap(int array[], int length);

#ifdef __cplusplus
}
#endif

#endif
