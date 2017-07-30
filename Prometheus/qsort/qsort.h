#ifndef QSORT
#define QSORT

#include <stdlib.h>
#include <stdint.h>

enum Pivot { FIRST, MEDIAN, LAST };

typedef int (*comparator)(void *, void *);

void q_sort(void *arr,        /* pointer to array to sort */
            int el_sz,        /* element size in bytes */
            int el_num,       /* number of elements in array */
            enum Pivot p,     /* pivot choosing algorithm */
            comparator cmp);  /* comparator */

void init_stats(void);            
int64_t cmp_num(void);

#endif
