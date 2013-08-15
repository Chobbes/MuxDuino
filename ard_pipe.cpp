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

#include "ard_pipe.h"


static PipeNode * create_pipe_node(ArdPipe pipe)
{
    PipeNode *node = allocate_memory(sizeof(PipeNode));

    node->pipe = pipe;
    node->next = NULL;

    return node;
}


/*
  Returns 0 if we can add the pipe to the list, 1 if the pipe is
  already in the list, and 2 if the pipe is invalid (input was defined
  as an output or vice versa).
*/

static int pipe_in_list_status(PipeList *list, ArdPipe pipe)
{
    if (NULL == list->first) {
	/* List is empty */
	return 0;
    }

    PipeList *cur_node = list->first;

    /* Need to check that our pipe is valid */
    while (NULL != cur_node) {
	ArdPipe cur_pipe = cur_node->pipe;

	if (cur_pipe == pipe) {
	    /* This pipe is already in the list */
	    return 1;
	}
	else if (cur_pipe.out_pin == pipe.in_pin) {
	    /* This input was previously defined as an input */
	    return 2;
	}
	else if (cur_pipe.in_pin == pipe.out_pin) {
	    /* This output was previously defined as an input */
	    return 2;
	}

	cur_node = cur_node->next;
    }

    return 0;
}


int pipe_list_add(PipeList *list, ArdPipe pipe)
{
    if (NULL == list->first) {
	/* List is empty... */
	node = create_pipe_node(pipe);

	list->first = node;
	list->tail = node;
    }

    int status = pipe_in_list_status(list, pipe);

    switch (status) {
    case 0:
	/* Need to add the pipe to the list */
	node = create_pipe_node(pipe);

	list->tail->next = node;
	list->tail = node;

	return 0;

    case 1:
	/* Already in list */
	return 0;

    case 2:
	/* Input / output mismatch */
	return 1;
    }
}
