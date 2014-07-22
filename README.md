mysql-zmq-plugin
================

ZeroMQ / ØMQ for MySQL

http://zeromq.org/event:zeromq-for-mysql

Build
-----
	# yum install zeromq3-devel
	
	# cmake .
	# make && make install

Install & uninstall
-------------------

	drop function zmq_client;
	drop function zmq_publish;
	
	create function zmq_client returns string soname 'libzeromq.so';
	create function zmq_publish returns string soname 'libzeromq.so';

	mysql> SELECT * FROM `mysql`.`func` LIMIT 1000;
	+--------------+-----+--------------+----------+
	| name         | ret | dl           | type     |
	+--------------+-----+--------------+----------+
	| image_crc32  |   0 | image.so     | function |
	| image_rename |   0 | image.so     | function |
	| image_move   |   0 | image.so     | function |
	| image_remove |   0 | image.so     | function |
	| image_check  |   0 | image.so     | function |
	| fifo_write   |   0 | fifo.so      | function |
	| fifo_read    |   0 | fifo.so      | function |
	| fifo_remove  |   0 | fifo.so      | function |
	| fifo_create  |   0 | fifo.so      | function |
	| zmq_publish  |   0 | libzeromq.so | function |
	| zmq_client   |   0 | libzeromq.so | function |
	+--------------+-----+--------------+----------+
	11 rows in set (0.00 sec)
	
Test
----

### 编译zeromq server 测试程序	
	cd test
	cmake .
	make
	./server
	
### 在mysql终端中运行测试SQL 	
	mysql> select zmq_client('tcp://localhost:5555','Hello world!');
	+---------------------------------------------------+
	| zmq_client('tcp://localhost:5555','Hello world!') |
	+---------------------------------------------------+
	| Hello world! OK                                   |
	+---------------------------------------------------+
	1 row in set (0.01 sec)
	
	mysql> select zmq_client('tcp://localhost:5555',mobile) from demo;
	+-------------------------------------------+
	| zmq_client('tcp://localhost:5555',mobile) |
	+-------------------------------------------+
	| 13113668891 OK                            |
	| 13113668892 OK                            |
	| 13113668893 OK                            |
	| 13322993040 OK                            |
	| 13588997745 OK                            |
	+-------------------------------------------+
	5 rows in set (0.03 sec)
	
手工编译
--------
	gcc -O3  -g  -I/usr/include/mysql -I/usr/include  -fPIC -lm -lz -shared -o libzeromq.so zeromq.c
	sudo mv libzeromq.so /usr/lib/mysql/plugin/
