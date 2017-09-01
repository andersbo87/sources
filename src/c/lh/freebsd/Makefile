CC=gcc

SQLCFLAGS=-I/usr/local/include/mysql
SQLLIBS="/usr/local/lib/mysql"

make:
	cc -g -o lh -L$(SQLLIBS) -lmysqlclient -pthread -lz $(SQLCFLAGS) ../main.c ../database_commands.c

install:
	install -g wheel -o root -m 555 lh /usr/local/bin/lh
	install -g wheel -o root -m 555 ../lh.1 /usr/local/man/man1/lh.1

clean:
	rm lh

uninstall:
	rm /usr/local/bin/lh /usr/local/man/man1/lh

deinstall:
	rm /usr/local/bin/lh /usr/local/man/man1/lh

