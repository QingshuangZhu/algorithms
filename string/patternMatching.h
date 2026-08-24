#ifndef PATTERN_MATCHING_H
#define PATTERN_MATCHING_H

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Return the zero-based index of the first match, or -1 when no match exists.
 * An empty pattern matches at index 0. Lengths must be nonnegative; a pointer
 * may be NULL only when its corresponding length is zero.
 */
int bruteForce1(const char pattern[], int patternLength,
                const char text[], int textLength);
int bruteForce2(const char pattern[], int patternLength,
                const char text[], int textLength);
/* KMP also returns -1 if its auxiliary allocation fails. */
int KMP(const char pattern[], int patternLength,
        const char text[], int textLength);

#ifdef __cplusplus
}
#endif

#endif
