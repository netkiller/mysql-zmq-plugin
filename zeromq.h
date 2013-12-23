my_bool zmq_read_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
char *zmq_read(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);
void zmq_read_deinit(UDF_INIT *initid);

my_bool zmq_write_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
char *zmq_write(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);
void zmq_write_deinit(UDF_INIT *initid);

char* concat(const char* str1, const char* str2)
{
    char* res;
    asprintf(&res, "%s%s", str1, str2);
    return res;
}