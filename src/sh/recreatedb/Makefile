UNAME_S != uname
all:

install:
	@echo Installing recreatedb on $(UNAME_S).
	mkdir -p /usr/local/sbin
.if $(UNAME_S) == Linux
	install -c -g root -o root -m 555 recreatedb.sh /usr/local/sbin/recreatedb
.else
	install -c -g wheel -o root -m 555 recreatedb.sh /usr/local/sbin/recreatedb
.endif
deinstall:	
	rm /usr/local/sbin/recreatedb

uninstall:
	rm /usr/local/sbin/recreatedb
