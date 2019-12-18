/*
 * heap
 */

#ifndef HEAP_H
#define HEAP_H

#ifdef __cplusplus
extern "C" {
#endif

void upAdjust(int array[], int length, int index);
void downAdjust(int array[], int length, int index);
void buildHeap(int array[], int length);

#ifdef __cplusplus
}
#endif

#endif