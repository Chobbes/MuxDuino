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

#ifndef MUX_INPUT_H
#define MUX_INPUT_H

/*
  Nodes for a singly linked list of inputs.
 */

typedef struct MuxInputNode {
    int in_pin;

    struct MuxInputNode *next;
} MuxInputNode;


/*
  Structure for a singly linked input list. The head and the tail will
  be the same if the list has one item.
 */

typedef struct MuxInputList {
    MuxInputNode *head;  /* First node in list, NULL if empty */
    MuxInputNode *tail;  /* Last node in list, NULL if empty */
} MuxInputList;


/*
  Arguments:
      list: The input list that we are adding to.

      in_pin: The input pin we want to add.

  Checks if the input pin is in the list already, and adds it if it is
  not (no sense storing duplicates).

 */

void mux_input_list_add(MuxInputList *list, int in_pin)


/*
  Arguments:
      list: The input list that we want to remove an input from.

      in_pin: The input pin we want to remove from the list.

  Checks if the input is in the list and removes it if it is.

 */


void mux_input_list_remove(MuxInputList *list, int in_pin)


#endif MUX_INPUT_H
