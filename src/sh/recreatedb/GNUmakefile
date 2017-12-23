UNAME_S = $(shell uname)
all:

install:
	@echo Installing recreatedb on $(UNAME_S).
	mkdir -p /usr/local/sbin
ifneq ($(UNAME_S),Linux)
	install -c -g wheel -o root -m 555 recreatedb.sh /usr/local/sbin/recreatedb
else
	install -c -g root -o root -m 555 recreatedb.sh /usr/local/sbin/recreatedb
endif
deinstall:	
	rm /usr/local/sbin/recreatedb

uninstall:
	rm /usr/local/sbin/recreatedb
