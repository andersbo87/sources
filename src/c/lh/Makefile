CC=gcc

SQLCFLAGS=-I/usr/local/include/mysql
SQLLIBS="-L/usr/local/lib/mysql"
CFLAGS=$(shell mysql_config --cflags)
LIB=$(shell mysql_config --libs)
UNAME_S=$(shell uname -s)
lh:
ifeq ($(UNAME_S), Linux)
	@echo "Dette programmet er avhengig av følgende biblioteker: libbsd-dev libmysqlclient-dev libreadline-dev"
	cc -g -o lh database_commands.c main.c $(shell mysql_config --cflags --libs) -lreadline -lmysqlclient -lbsd
else
	cc -g -o lh $(LIB) -lmysqlclient -pthread -lz $(CFLAGS) main.c database_commands.c
endif


install: lh
	mkdir -p /usr/local/bin /usr/local/man/man1
ifeq ($(UNAME_S), Linux)
	install -g root -o root -m 555 lh /usr/local/bin/lh
	install -g root -o root -m 555 lh.1 /usr/local/man/man1/lh.1
else
	install -g wheel -o root -m 555 lh /usr/local/bin/lh
	install -g wheel -o root -m 555 lh.1 /usr/local/man/man1/lh.1
endif

clean:
	rm lh
	rm -rf lh.dSYM/
uninstall:
	rm /usr/local/bin/lh /usr/local/man/man1/lh

deinstall:
	rm /usr/local/bin/lh /usr/local/man/man1/lh

