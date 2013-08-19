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

#include "mux_input.h"
#include "mem_alloc.h"


/* Allocate an input node for a given input pin */
static MuxInputNode * create_input_node(int in_pin)
{
    MuxInputNode *node = allocate_memory(sizeof(MuxInputNode));

    node->in_pin = in_pin;
    node->next = NULL;

    return node;
}


/* Find the input node for the in_pin. Returns NULL if it is not in the list */
MuxInputNode * find_input_node(MuxInputList *list, int in_pin)
{
    MuxInputNode *node = list->head;

    while (NULL != node) {
	if (pipe.in_pin == node->in_pin) {
	    return node;
	}

	node = node->next;
    }

    return NULL;
}


void mux_input_list_add(MuxInputList *list, int in_pin)
{
    if (NULL == list->head) {
        /* List is empty... */
        MuxInputNode *node = create_input_node(in_pin);

	list->head = node;
	list->tail = node;
    }

    if (!find_input_node(list, in_pin)) {
	/* Need to add the pipe's input to the list */
	MuxInputNode *node = create_input_node(in_pin);
	
	list->tail->next = node;
	list->tail = node;
    }
}


void mux_input_list_remove(MuxInputList *list, int in_pin)
{
    MuxInputNode *current_node = list->head;
    MuxInputNode *previous_node = NULL;

    /* Search list for our in_pin to remove it */
    while (NULL != current_node) {
	int current_in_pin = current_node->in_pin;

	if (current_in_pipe == in_pin) {
	    /* Found the input in the list! Remove it... */
	    if (NULL != previous_node) {
		previous_node->next = current_node->next;
	    }

	    /* Adjust head and tail if necessary */
	    if (current_node == list->head) {
		list->head = list->head->next;
	    }

	    if (current_node == list->tail) {
		list->tail = previous_node;
	    }

	    free_memory(current_node);
	    return;
	}

	previous_node = current_node;
	current_node = current_node->next;
    }
}
