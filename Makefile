.POSIX:
.SUFFIXES:

include config.mk

# flags for compiling
DWLCPPFLAGS = -I. -DWLR_USE_UNSTABLE -D_POSIX_C_SOURCE=200809L -DVERSION=\"$(VERSION)\" $(XWAYLAND)
DWLDEVCFLAGS = -pedantic -Wall -Wextra -Wdeclaration-after-statement -Wno-unused-parameter -Wno-sign-compare -Wshadow -Wunused-macros\
	-Werror=strict-prototypes -Werror=implicit -Werror=return-type -Werror=incompatible-pointer-types

# CFLAGS / LDFLAGS
PKGS      = wlroots wayland-server xkbcommon libinput $(XLIBS)
DWLCFLAGS = `$(PKG_CONFIG) --cflags $(PKGS)` $(DWLCPPFLAGS) $(DWLDEVCFLAGS) $(CFLAGS)
LDLIBS    = `$(PKG_CONFIG) --libs $(PKGS)` $(LIBS)

all: dwl
dwl: dwl.o util.o
	$(CC) dwl.o util.o $(LDLIBS) $(LDFLAGS) $(DWLCFLAGS) -o $@
dwl.o: dwl.c config.mk config.h client.h xdg-shell-protocol.h wlr-layer-shell-unstable-v1-protocol.h
util.o: util.c util.h

# wayland-scanner is a tool which generates C headers and rigging for Wayland
# protocols, which are specified in XML. wlroots requires you to rig these up
# to your build system yourself and provide them in the include path.
WAYLAND_SCANNER   = `$(PKG_CONFIG) --variable=wayland_scanner wayland-scanner`
WAYLAND_PROTOCOLS = `$(PKG_CONFIG) --variable=pkgdatadir wayland-protocols`

xdg-shell-protocol.h:
	$(WAYLAND_SCANNER) server-header \
		$(WAYLAND_PROTOCOLS)/stable/xdg-shell/xdg-shell.xml $@
wlr-layer-shell-unstable-v1-protocol.h:
	$(WAYLAND_SCANNER) server-header \
		protocols/wlr-layer-shell-unstable-v1.xml $@

config.h:
	cp config.def.h $@
clean:
	rm -f dwl *.o *-protocol.h

dist: clean
	mkdir -p dwl-$(VERSION)
	cp -R LICENSE* Makefile README.md client.h config.def.h\
		config.mk protocols dwl.1 dwl.c util.c util.h\
		dwl-$(VERSION)
	tar -caf dwl-$(VERSION).tar.gz dwl-$(VERSION)
	rm -rf dwl-$(VERSION)

# install rules
install: dwl
	install -Dm755 dwl $(DESTDIR)$(PREFIX)/bin/dwl
	install -Dm644 dwl.1 $(DESTDIR)$(MANDIR)/man1/dwl.1
	install -Dm755 dwl_start $(DESTDIR)${PREFIX}/bin/dwl_start
	install -D dwl.desktop /usr/share/wayland-sessions/dwl.desktop

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/dwl
	rm -f $(DESTDIR)$(PREFIX)/bin/dwl_start
	rm -f /usr/share/wayland-sessions/dwl.desktop

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CPPFLAGS) $(DWLCFLAGS) -c $<
