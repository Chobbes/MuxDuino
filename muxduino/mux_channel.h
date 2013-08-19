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

#ifndef MUX_CHANNEL_H
#define MUX_CHANNEL_H

#include "mux_input.h"
#include "mux_pipe.h"


/*
  A MuxChannelNode is a single element in a linked list of channels.

  Fields:
      channel: The number for the channel that this represents.

      inputs: List of inputs on the channel.

      next: Next node in the linked list, NULL on the last node.
 */

typedef struct MuxChannelNode {
    int channel;
    MuxInputList inputs;

    struct MuxChannelNode *next;
} MuxChannelNode;


/*
  List of channels. Head and tail will be NULL if empty, and the head will be
 */

typedef struct MuxChannelList {
    MuxChannelNode *head;
    MuxChannelNode *tail;
} MuxChannelList;


/*
  Arguments:
      list: The channel list that we want to search.

      channel: The number of the channel we want to find.

  Returns a pointer to the channel node which has the given channel
  number. If there is so such channel node in the list then NULL is
  returned.

 */

MuxChannelNode * find_channel_node(MuxChannelList *list, int channel);


/*
  Arguments:
      list: The channel list we are adding to.

      pipe: The pipe with the channel that we want to add.

  Makes sure that the channel / input of the pipe is in the channel
  list. This function may allocate memory if the channel / input is
  not already in the list. If the channel / input pair is already in
  the list then the function will do nothing -- duplicates are
  ignored.

 */

void mux_channel_list_add(MuxChannelList *list, MuxPipe pipe);


/*
  Arguments:
      list: The channel list we are removing from.

      pipe: The pipe with the channel that we want to remove.

  Removes the channel's input if it is in the list and frees the
  memory. If the channel has no more inputs after it is removed then
  the channel node will be freed as well.

 */

void mux_channel_list_remove(MuxChannelList *list, MuxPipe pipe);

#endif
