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

#include "mux_pipe.h"
#include "mux_input.h"
#include "mem_alloc.h"


/* Allocate an input node for a given a pipe */
static MuxChannelNode * create_channel_node(MuxPipe pipe)
{
    MuxChannelNode *node = allocate_memory(sizeof(MuxChannelNode));

    node->channel = pipe.channel;

    /* Set up the inputs list */
    node->inputs.head = NULL;
    node->inputs.tail = NULL;
    mux_input_list_add(&node->inputs, pipe.in_pin);

    node->next = NULL;

    return node;
}


/* Find a channel node in a list. Returns NULL if it is not in the list */
MuxChannelNode * find_channel_node(MuxChannelList *list, int channel)
{
    MuxChannelNode *node = list->head;

    while (NULL != node) {
	if (channel == node->channel) {
	    return node;
	}

	node = node->next;
    }

    return NULL;
}


void mux_channel_list_add(MuxChannelList *list, MuxPipe pipe)
{
    if (NULL == list->head) {
        /* List is empty... */
        MuxChannelNode *node = create_channel_node(pipe);

	list->head = node;
	list->tail = node;

	return;
    }

    MuxChannelNode *node = find_channel_node(list, pipe.channel);

    if (!node) {
	/* Need to create a new channel node */
	MuxChannelNode *node = create_channel_node(pipe);
	
	list->tail->next = node;
	list->tail = node;
    }
    else {
	/* Need to add our input to the channel node */
	mux_input_list_add(&node->inputs, pipe.in_pin);
    }
}


void mux_channel_list_remove(MuxChannelList *list, MuxPipe pipe)
{
    MuxChannelNode *current_node = list->head;
    MuxChannelNode *previous_node = NULL;

    /* Search list for our in_pin to remove it */
    while (NULL != current_node) {
	int current_channel = current_node->channel;

	if (current_channel == pipe.channel) {
	    mux_input_list_remove(&current_node->inputs, pip.in_pin);

	    if (NULL == current_node->inputs.head) {
		/* No more inputs, need to remove this channel */
		if (NULL != previous_node) {
		    previous_node->next = current_node->next;
		}

		/* Adjust the head and tail if necessary */
		if (current_node == list->head) {
		    list->head = list->head->next;
		}

		if (current_node == list->tail) {
		    list->tail = previous_node;
		}

		free_memory(current_node);
	    }

	    return;
	}

	previous_node = current_node;
	current_node = current_node->next;
    }
}
