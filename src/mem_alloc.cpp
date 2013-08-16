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

#include "mem_alloc.h"

/* If true count allocations and frees, else don't */
const static bool count_allocs = true;

/* Counters for allocations and frees */
static unsigned long num_allocs = 0;
static unsigned long num_frees = 0;


void * allocate_memory(size_t size)
{
    if (count_allocs) {
	++num_allocs;
    }

    return malloc(size);
}


void free_memory(void *ptr)
{
    if (count_allocs) {
	++num_frees;
    }

    free(ptr);
}


unsigned long total_allocations()
{
    return num_allocs;
}


unsigned long total_frees()
{
    return num_frees;
}
