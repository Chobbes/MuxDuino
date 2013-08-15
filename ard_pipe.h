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

#ifndef ARD_PIPE_H
#define ARD_PIPE_H

/*
  Structure for a pin redirection. This represents a connection
  between the input pin 'in_pin', and the output pin, 'out_pin'.

  What we will do to make this pipe functional is read the digital
  value for the input, and then immediately write that value on the
  output pin.
 */

typedef struct ArdPipe {
    int in_pin;
    int out_pin;
} ArdPipe;


/*
  Nodes for a singly linked list of pipes.
 */

typedef struct PipeNode {
    ArdPipe pipe;
    struct PipeNode *next;
} PipeNode;


/*
  Singly linked pipe list.
 */

typedef struct PipeList {
    PipeNode *head;  /* First node in the list, NULL if empty */
    PipeNode *tail;  /* Final node in the list, NULL if empty */
} PipeList;


/*
  Add a pipe to a pipe list - if this pipe is already within the pipe
  list then it will just be ignored. We do not need duplicated pipes
  within a list.

  This will also check if a pipe has an input which was previously
  defined to be an output, or vice versa. If this is the case nothing
  will be done and an error code of the value 1 will be returned. This
  function returns 0 upon success.
 */

int pipe_list_add(PipeList *list, ArdPipe pipe);


/*
  Remove a connection from a pipe list, if it doesn't occur in the
  pipe list then we just ignore it.
 */

void pipe_list_remove(PipeList *list, ArdPipe pipe);

#endif ARD_PIPE_H
