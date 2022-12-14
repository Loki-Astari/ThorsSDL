THORSANVIL_ROOT             = $(realpath ../../)

%/Windows.o:				FILE_WARNING_FLAGS += -Wno-unused-private-field

TARGET                      = display.app ThorsWidgets.slib
CXXFLAGS					+= $(SDL_CFLAGS)
LDLIBS						+= $(SDL_LIBS)
LINK_LIBS					+= ThorsUI

UNITTEST_LINK_LIBS			+= ThorsUI

include $(THORSANVIL_ROOT)/build/tools/Makefile
