# dwm - dynamic window manager
# See LICENSE file for copyright and license details.

include config.mk

SRC = drw.c dwm.c util.c
OBJ = ${SRC:.c=.o}

all: options dwm

options:
	@echo dwm build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk

config.h:
	cp config.def.h $@

dwm: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f dwm ${OBJ} dwm-${VERSION}.tar.gz

dist: clean
	mkdir -p dwm-${VERSION}
	cp -R LICENSE Makefile README config.def.h config.mk\
		dwm.1 drw.h util.h ${SRC} dwm.png transient.c dwm-${VERSION}
	tar -cf dwm-${VERSION}.tar dwm-${VERSION}
	gzip dwm-${VERSION}.tar
	rm -rf dwm-${VERSION}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	cp -f dwm ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/dwm
	cp -f sdmenu ${DESTDIR}${PREFIX}/bin
	cp -f pickchar ${DESTDIR}${PREFIX}/bin
	cp -f screenshot ${DESTDIR}${PREFIX}/bin
	mkdir -p ${DESTDIR}${PREFIX}/share/dwm
	cp -f shortcuts.md ${DESTDIR}${PREFIX}/share/dwm
	chmod 644 ${DESTDIR}${PREFIX}/share/dwm/shortcuts.md
	chmod 755 ${DESTDIR}${PREFIX}/bin/sdmenu
	chmod 755 ${DESTDIR}${PREFIX}/bin/pickchar
	chmod 755 ${DESTDIR}${PREFIX}/bin/screenshot
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" < dwm.1 > ${DESTDIR}${MANPREFIX}/man1/dwm.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/dwm.1

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/dwm\
		${DESTDIR}${MANPREFIX}/man1/dwm.1 \
		${DESTDIR}${PREFIX}/bin/sdmenu \
		${DESTDIR}${PREFIX}/bin/pickchar \
		${DESTDIR}${PREFIX}/bin/screenshot \
		${DESTDIR}${PREFIX}/share/dwm/shortcuts.md \
		${DESTDIR}${PREFIX}/share/dwm

.PHONY: all options clean dist install uninstall
