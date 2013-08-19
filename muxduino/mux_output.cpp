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
#include "mux_output.h"
#include "mux_channel.h"
#include "mem_alloc.h"

typedef struct MuxOutputNode {
    int out_pin;

    int channel_num;
    MuxChannelNode *current_channel;

    MuxChannelList channels;

    struct MuxOutputNode *next;
} MuxOutputNode;


/* Allocate an input node for a given pipe */
static MuxOutputNode * create_output_node(MuxPipe pipe)
{
    MuxOutputNode *node = allocate_memory(sizeof(MuxOutputNode));

    node->out_pin = pipe.out_pin;
    node->channel = pipe.channel;

    /* Set up the channels list */
    node->channels.head = NULL;
    node->channels.tail = NULL;
    mux_channel_list_add(&node->channels, pipe);

    node->current_channel = node->channels.head;
    node->next = NULL;

    return node;
}


/* Find an output node in a list, returns NULL if not found. */
MuxOutputNode * find_output_node(MuxChannelList *list, int out_pin)
{
    MuxOutputNode *node = list->head;

    while (NULL != node) {
	if (out_pin == node->out_pin) {
	    return node;
	}

	node = node->next;
    }

    return NULL;
}


void mux_output_list_add(MuxOutputList *list, MuxPipe pipe)`
{
    if (NULL == list->head) {
        /* List is empty... */
        MuxChannelNode *node = create_channel_node(pipe);

	list->head = node;
	list->tail = node;

	return;
    }

    if (!channel_in_list(list, pipe)) {
	/* Need to add the pipe's input to the list */
	MuxChannelNode *node = create_channel_node(pipe);
	
	list->tail->next = node;
	list->tail = node;
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
	    if (input_in_list(&current_node->inputs, pipe.in_pin)) {
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
	}

	previous_node = current_node;
	current_node = current_node->next;
    }
}
