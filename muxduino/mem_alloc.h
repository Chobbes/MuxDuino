/* Copyright (C) 2013 Calvin Beck

  Permission is hereby granted, free of charge, to any person
  obtaining a copy of this software and associated documentation files
  (the "Software"), to deal in the Software without restriction,
  including without limitation the rights to use, copy, modify, merge,
  publish, distribute, sublicense, and/or sell copies of the Software,
  and to permit persons to whom the Software is furnished to do so,
  subject to the following conditions:

  The above copyright notice and this permission notice shall be
  included in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
  ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

*/

#ifndef MEM_ALLOC_H
#define MEM_ALLOC_H

/*
  Memory allocation helper functions. This is useful if we want to do
  something to keep track of allocations or whatever, but it's
  basically just a wrapper for malloc() and free().
 */

#include <stdlib.h>


/*
  Function for allocating a chunk of memory, returns a pointer to
  that memory. This is a wrapper for malloc().
 */

void * allocate_memory(size_t size);


/*
  Function for freeing a chunk of memory previously allocated by
  allocate_memory(). This is a wrapper for free().
 */

void free_memory(void *ptr);


/*
  Functions for retrieving memory usage statistics. These are only
  useful if the count_allocs boolean in mem_alloc.cpp is set to true,
  otherwise we do not keep track of the statistics.

  The total_allocations() function will return the number of times
  allocate_memory() has been called, and total_frees() counts the
  number of times we have called free_memory(). For each allocation
  there should be a corresponding free. These numbers are a guide, but
  not a guarantee - you can still make useless free_memory() calls
  which will bump up the number of total frees for instance.
 */

unsigned long total_allocations();
unsigned long total_frees();

#endif
