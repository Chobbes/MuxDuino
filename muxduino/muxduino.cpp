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

#include "muxduino.h"
#include "mux_pipe.h"
#include "mux_output.h"
#include "mux_channel.h"

#include "Arduino.h"


/* Main list for muxduino outputs -- starts empty */
static MuxOutputList mux_outs = {NULL, NULL};


int register_pipe(MuxPipe pipe)
{
    /* Check if our input was previously registered as an output */
    if (find_output_node(&mux_outs, pipe.in_pin)) {
	return 1;
    }

    /* Check if our output is ever defined as an input */
    MuxOutputNode *out_node = mux_outs.head;
    while (out_node) {
	MuxChannelNode *channel_node = out_node->channels.head;
	while (channel_node) {
	    if (find_input_node(&channel_node->inputs, pipe.out_pin)) {
		return 2;
	    }

	    channel_node = channel_node->next;
	}

	out_node = out_node->next;
    }

    /* Pipe is good and valid, add it to the outputs */
    mux_output_list_add(&mux_outs, pipe);

    pinMode(pipe.in_pin, INPUT);
    pinMode(pipe.out_pin, OUTPUT);

    return 0;
}


void unregister_pipe(MuxPipe pipe)
{
    mux_output_list_remove(&mux_outs, pipe);
}


void set_output_channel(int out_pin, int new_channel)
{
    MuxOutputNode *node = find_output_node(&mux_outs, out_pin);

    node->channel_num = new_channel;

    /* Need to adjust the current channel */
    node->current_channel = find_channel_node(&node->channels,
					      node->channel_num);
}


void mux_update()
{
    MuxOutputNode *out_node = mux_outs.head;
    while (out_node) {
	MuxChannelNode *current_channel = out_node->current_channel;

	if (out_node->current_channel) {
	    MuxInputNode *in_node = current_channel->inputs.head;

	    while (in_node) {
		if (HIGH == digitalRead(in_node->in_pin)) {
		    digitalWrite(out_node->out_pin, HIGH);
		    break;
		}
		else if (NULL == in_node->next) {
		    digitalWrite(out_node->out_pin, LOW);
		}

		in_node = in_node->next;
	    }
	}

	out_node = out_node->next;
    }
}

