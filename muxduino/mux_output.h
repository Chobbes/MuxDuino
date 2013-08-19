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

#ifndef MUX_OUTPUT_H
#define MUX_OUTPUT_H

#include "mux_channel.h"


/*
  Output structure. This is used to tie an output pin (out_pin) to a
  collection of channels which consist of various inputs.

  This is also a node in a singly linked list of outputs.
 */

typedef struct MuxOutputNode {
    int out_pin;

    int channel_num;
    MuxChannelNode *current_channel;

    MuxChannelList channels;

    struct MuxOutputNode *next;
} MuxOutputNode;


/*
  List of outputs. Head and tail will be NULL if empty, and the head
  is the same as the tail if the list has one item.
 */

typedef struct MuxOutputList {
    MuxOutputNode *head;
    MuxOutputNode *tail;
} MuxOutputList;


/*
  Arguments:
      list: The list that we want to search.

      out_pin: The output pin number that we are searching for.

  Returns a pointer to the output node with the out_pin, or NULL if it
  is not found in the list.

 */

MuxOutputNode * find_output_node(MuxOutputList *list, int out_pin);


/*
  Arguments:
      list: The list that we are adding to.

      pipe: The pipe that we want to add.

  Adds the pipe to the outputs, may allocate memory. Will not do
  anything if the output, channel, and input are already in the output
  list.

 */

void mux_output_list_add(MuxOutputList *list, MuxPipe pipe);


/*
  Arguments:
      list: The list that we are removing from.

      pipe: The pipe that we want to remove.

  Removes the appropriate pipe from the list. May remove an output
  node if it has no remaining channels. This also readjusts the
  current_channel pointer if the current channel disappears to be
  NULL.

 */

void mux_output_list_remove(MuxOutputList *list, MuxPipe pipe);

#endif
