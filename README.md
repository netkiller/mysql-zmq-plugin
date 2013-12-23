mysql-zmq-plugin
================

ZeroMQ / ØMQ for MySQL

	cmake .
	make && make install
	
	drop function zmq_write;
	drop function zmq_read;
	
	create function zmq_write returns string soname 'libzeromq.so';
	create function zmq_read returns string soname 'libzeromq.so';

	select zmq_write('tcp://localhost:5555','Hello world!');
	select zmq_read('tcp://localhost:5555');
	
手工编译
--------
	gcc -O3  -g  -I/usr/include/mysql -I/usr/include  -fPIC -lm -lz -shared -o zeromq.so zeromq.c
	sudo mv zeromq.so /usr/lib/mysql/plugin/
