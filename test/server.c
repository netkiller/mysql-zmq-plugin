#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

int main (int argc,char**argv)
{
	// Socket to talk to clients
	void *context = zmq_ctx_new ();
	void *zmqsocket = zmq_socket (context, ZMQ_REP);
	int rc = zmq_bind (zmqsocket, "tcp://*:5555");
	assert (rc == 0);
	char *recv;
	char *send;
	
	
	while (1) {

		zmq_msg_t buffer={0};
		zmq_msg_init (&buffer);
		zmq_msg_recv (&buffer, zmqsocket, 0);
		int size = zmq_msg_size (&buffer);
		char *string = malloc (size + 1);
		memset(string,0,size+1);
		memcpy (string, zmq_msg_data (&buffer), size);
		if(size > 0){
			asprintf(&recv, "%s", string);
			printf ("Received: %s\n", recv);
		}
		free(string);
		zmq_msg_close (&buffer);
		
		asprintf(&send, "%s OK", recv); 
		
		//zmq_msg_t buffer={0};
		zmq_msg_init_size (&buffer, strlen(send));
		memcpy (zmq_msg_data (&buffer), send, strlen(send));
		
		if(zmq_msg_send(&buffer, zmqsocket, 0) == 0){
			printf ("Sent: %s\n", send);
		}
		
		zmq_msg_close (&buffer);
	}
		
	return 0;
}
