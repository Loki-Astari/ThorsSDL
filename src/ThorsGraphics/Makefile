THORSANVIL_ROOT             = $(realpath ../../)

TARGET                      = ThorsGraphics.slib display.app
CXXFLAGS					+= $(SDL_CFLAGS)
LDLIBS						+= $(SDL_LIBS)
LINK_LIBS					+= ThorsUI

UNITTEST_LINK_LIBS			+= ThorsUI

include $(THORSANVIL_ROOT)/build/tools/Makefile
