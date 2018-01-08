/*
Homepage: http://netkiller.github.io/
Author: netkiller<netkiller@msn.com>
*/
#include <stdlib.h>
#include <stdio.h>
#include <mysql.h>
#include <string.h>
#include <error.h>
#include <zmq.h>

#include "zeromq.h"

/* ------------------------ zmq_client ----------------------------- */

my_bool zmq_client_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 2)
  {
    strncpy(message, "two arguments must be supplied: zmq_client('socket','message').", MYSQL_ERRMSG_SIZE);
    return 1;
  }

  args->arg_type[0]= STRING_RESULT;
    return 0;
}

char *zmq_client(UDF_INIT *initid, UDF_ARGS *args,
                __attribute__ ((unused)) char *result,
               unsigned long *length,
                __attribute__ ((unused)) char *is_null,
                __attribute__ ((unused)) char *error)
{

	char *text;
	text = "NULL";
	int status = -1;
	
	void *context = zmq_ctx_new ();
	void *zmqsocket = zmq_socket (context, ZMQ_REQ);
	int timeout = 250;
        zmq_setsockopt(zmqsocket, ZMQ_SNDTIMEO, &timeout, sizeof timeout);
        zmq_setsockopt(zmqsocket, ZMQ_RCVTIMEO, &timeout, sizeof timeout);
        zmq_setsockopt(zmqsocket, ZMQ_LINGER, &timeout, sizeof timeout);
	zmq_connect (zmqsocket, args->args[0]);

	zmq_msg_t buffer={0};
	zmq_msg_init_size (&buffer, strlen(args->args[1]));
	memcpy (zmq_msg_data (&buffer), args->args[1], strlen(args->args[1]));
	
	if(zmq_msg_send(&buffer, zmqsocket, 0) != -1){
		status = 1;
	}else{
		text="NULL";
	}
	zmq_msg_close (&buffer);
	if(status){
		zmq_msg_t buffer={0};
		zmq_msg_init (&buffer);

		zmq_msg_recv (&buffer, zmqsocket, 0);

		int size = zmq_msg_size (&buffer);
		char *string = malloc (size + 1);
		memset(string,0,size+1);
		memcpy (string, zmq_msg_data (&buffer), size);
		if(size > 0){
			asprintf(&text, "%s", string);
		}
		free(string);
		zmq_msg_close (&buffer);
	}
	zmq_close (zmqsocket);
	zmq_ctx_destroy (context);
	
	*length = strlen(text);
	return ((char *)text);
}

void zmq_client_deinit(UDF_INIT *initid)
{
   return;
}

/* ------------------------ zmq_publish ----------------------------- */

my_bool zmq_publish_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 2)
  {
    strncpy(message, "two arguments must be supplied: zmq_publish('socket','message').", MYSQL_ERRMSG_SIZE);
    return 1;
  }

  args->arg_type[0]= STRING_RESULT;
    return 0;
}

char *zmq_publish(UDF_INIT *initid, UDF_ARGS *args,
                __attribute__ ((unused)) char *result,
               unsigned long *length,
                __attribute__ ((unused)) char *is_null,
                __attribute__ ((unused)) char *error)
{

	  char *status;

    void *context = zmq_ctx_new ();
    void *publisher = zmq_socket (context, ZMQ_PUB);
    int rc = zmq_bind (publisher, args->args[0]);
    //assert (rc == 0);
        //  Send message to all subscribers

    zmq_close (publisher);
    zmq_ctx_destroy (context);
  
	/* 等有时间再完善 */
//	status = "等有时间再完善";
	status = "This is in english";

	*length = strlen(status);
	return ((char *)status);
}

void zmq_publish_deinit(UDF_INIT *initid)
{
   return;
}
