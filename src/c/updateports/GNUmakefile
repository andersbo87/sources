UNAME_S = $(shell uname)
DOT = $(shell cc --version 2>/dev/null)
FILE=/usr/bin/xdotool
ALTFILE=/usr/local/bin/xdotool
updateports:
ifneq ($(UNAME_S), SunOS)
ifeq ($(shell test -e $(FILE) && echo -n yes), yes)
	@echo Found xdotool at $(FILE).
else ifeq ($(shell test -e $(ALTFILE) && echo -n yes), yes)
	@echo Found xdotool at $(ALTFILE).
else
	FILE_EXISTS=0
	$(error File $(ALTFILE) or $(FILE) does not exist)
endif
endif
ifdef DOT
ifneq ($(DOT), )
	@echo "Found $(DOT)"
	cc -o updateports updateports.c
else
	@echo "Not found. Trying gcc..."
ifeq ($(UNAME_S), SunOS)
	gcc -o updateports -lnsl updateports.c
else
	gcc -o updateports updateports.c
endif
endif
endif
install: updateports
ifneq ($(UNAME_S), Linux)
	mkdir -p /usr/local/sbin/
ifeq ($(UNAME_S), SunOS)
	mkdir -p /usr/local/man/man8
	/usr/sbin/install -c /usr/local/sbin/ -m 755 -u root -g root updateports
	/usr/sbin/install -c /usr/share/man/man8 -m 755 -u root -g root updateports.8
else
	install -o root -g wheel updateports /usr/local/sbin/updateports
ifeq ($(UNAME_S), NetBSD)
	install -o root -g wheel updateports.8 /usr/pkg/man/man8/updateports.8
else
ifeq ($(UNAME_S), OpenBSD)
	install -o root -g wheel updateports.8 /usr/local/man/man8/updateports.8
else
	install -o root -g wheel updateports.8 /usr/share/man/man8/updateports.8
endif
endif
endif
else
	mkdir -p /usr/local/sbin/
	install -o root -g root updateports /usr/local/sbin/updateports
	install -o root -g root updateports.8 /usr/share/man/man8/updateports.8
endif
clean:
	rm -f updateports
uninstall:
	rm -f /usr/local/sbin/updateports
ifeq ($(UNAME_S), SunOS)
	rm -f /usr/share/man/man8/updateports.8
else
ifeq ($(UNAME_S), Linux)
	rm -f /usr/share/man/man8/updateports.8
else
ifeq ($(UNAME_S), NetBSD)
	rm -f /usr/pkg/man/man8/updateports.8
else
	rm -f /usr/local/man/man8/updateports.8
endif
endif
endif
deinstall:
	rm -f /usr/local/sbin/updateports
ifeq ($(UNAME_S), SunOS) 
	rm -f /usr/share/man/man8/updateports.8
else
ifeq ($(UNAME_S), Linux)
	rm -f /usr/share/man/man8/updateports.8
else
ifeq ($(UNAME_S), NetBSD)
	rm -f /usr/pkg/man/man8/updateports.8
else
	rm -f /usr/local/man/man8/updateports.8
endif
endif
endif
