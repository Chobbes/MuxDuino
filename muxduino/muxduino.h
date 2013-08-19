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

#ifndef MUXDUINO_H
#define MUXDUINO_H

/*
  Interface to the MuxDuino Arduino multiplexing library.
 */

#includo "mux_pipe.h"


/*
  Arguments:
      pipe: The pipe we want to register with MuxDuino.

  Registers a pipe with the main pipe list for connections. This will
  allocate some memory.
 */
int register_pipe(MuxPipe pipe);


/*
  Arguments:
      pipe: The pipe we want MuxDuino to forget about.

  Removes a pipe from the main pipe list (does nothing if the pipe
  does not exist).
 */
void unregister_pipe(MuxPipe pipe);


/*
  Arguments:
      out_pin: The output that we want to change the channel of.

      new_channel: The new channel that we want to set.

  Changes the currently selected channel for the output.
 */

void set_output_channel(int out_pin, int new_channel);


/*
  This function loops through all of the pipes, and does the
  appropriate reads and writes.
 */

void mux_update();

#endif
