CC=gcc

SQLCFLAGS=-I/usr/local/include/mysql
SQLLIBS="-L/usr/local/lib/mysql"
CFLAGS=$(shell mysql_config --cflags)
LIB=$(shell mysql_config --libs)
lh:
	cc -g -o lh $(LIB) -lmysqlclient -pthread -lz $(CFLAGS) main.c database_commands.c


install: lh
	install -g wheel -o root -m 555 lh /usr/local/bin/lh
	install -g wheel -o root -m 555 lh.1 /usr/local/man/man1/lh.1

clean:
	rm lh

uninstall:
	rm /usr/local/bin/lh /usr/local/man/man1/lh

deinstall:
	rm /usr/local/bin/lh /usr/local/man/man1/lh

