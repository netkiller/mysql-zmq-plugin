/*
Homepage: http://netkiller.github.io/
Author: netkiller<netkiller@msn.com>
*/
#include <stdlib.h>
#include <stdio.h>
#include <mysql.h>
#include <string.h>
#include <zmq.h>

#include "zeromq.h"

/* ------------------------ zmq_read ----------------------------- */

my_bool zmq_read_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{

  if (args->arg_count != 1)
  {
    strncpy(message, "one arguments must be supplied: zmq_read('<socket>').", MYSQL_ERRMSG_SIZE);
    return 1;
  }

  args->arg_type[0]= STRING_RESULT;

  return 0;
}

char *zmq_read(UDF_INIT *initid, UDF_ARGS *args,
                __attribute__ ((unused)) char *result,
               unsigned long *length,
                __attribute__ ((unused)) char *is_null,
                __attribute__ ((unused)) char *error)
{

    char *data;

	void *context = zmq_ctx_new ();
	void *zmqsocket = zmq_socket (context, ZMQ_REP);
	zmq_connect (zmqsocket, args->args[0]);	
	
	zmq_msg_t buffer={0};
	zmq_msg_init (&buffer);
	zmq_recvmsg (zmqsocket, &buffer,0);
	int size = zmq_msg_size (&buffer);
	char *string = malloc (size + 1);
	memset(string,0,size+1);
	memcpy (string, zmq_msg_data (&buffer), size);
	if(size > 0){
		asprintf(&data, "%s", string);
	}
	free(string);
	zmq_msg_close (&buffer);
	zmq_close (zmqsocket);
	zmq_ctx_destroy (context);
	
    *length = strlen(data);
    return ((char *)data);

}

void zmq_read_deinit(UDF_INIT *initid)
{
  return;
}

/* ------------------------ zmq_write ----------------------------- */

my_bool zmq_write_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 2)
  {
    strncpy(message, "two arguments must be supplied: zmq_write('socket','message').", MYSQL_ERRMSG_SIZE);
    return 1;
  }

  args->arg_type[0]= STRING_RESULT;
    return 0;
}

char *zmq_write(UDF_INIT *initid, UDF_ARGS *args,
                __attribute__ ((unused)) char *result,
               unsigned long *length,
                __attribute__ ((unused)) char *is_null,
                __attribute__ ((unused)) char *error)
{

	char *status;
	
	void *context = zmq_ctx_new ();
	void *zmqsocket = zmq_socket (context, ZMQ_REQ);
	zmq_connect (zmqsocket, args->args[0]);

	zmq_msg_t buffer={0};
	zmq_msg_init_size (&buffer, strlen(args->args[1]));
	memcpy (zmq_msg_data (&buffer), args->args[1], strlen(args->args[1]));
	
	status = "false";
	if(zmq_sendmsg(zmqsocket, &buffer, 0) == 0){
		status = "true";
	}
	zmq_msg_close (&buffer);
	zmq_close (zmqsocket);
	zmq_ctx_destroy (context);

	*length = strlen(status);
	return ((char *)status);
}

void zmq_write_deinit(UDF_INIT *initid)
{
   return;
}