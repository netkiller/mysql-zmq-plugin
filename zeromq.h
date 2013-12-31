my_bool zmq_client_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
char *zmq_client(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);
void zmq_client_deinit(UDF_INIT *initid);

my_bool zmq_publish_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
char *zmq_publish(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);
void zmq_publish_deinit(UDF_INIT *initid);

char* concat(const char* str1, const char* str2)
{
    char* res;
    asprintf(&res, "%s%s", str1, str2);
    return res;
}