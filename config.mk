_VERSION = 0.3.1-dev
VERSION  = `git describe --long --tags --dirty 2>/dev/null || echo $(_VERSION)`

PKG_CONFIG = pkg-config

# paths
PREFIX = /usr/local
MANDIR = $(PREFIX)/share/man

# Compile flags that can be used
#CFLAGS = -pedantic -Wall -Wextra -Werror -Wno-unused-parameter -Wno-sign-compare -Wno-unused-function -Wno-unused-variable -Wno-unused-result -Wdeclaration-after-statement

# Uncomment to build XWayland support
#XWAYLAND = -DXWAYLAND
#CFLAGS += -DXWAYLAND
#XLIBS = xcb
XWAYLAND =
XLIBS =
