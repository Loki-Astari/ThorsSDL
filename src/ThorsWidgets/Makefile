THORSANVIL_ROOT             = $(realpath ../../)

%/Windows.o:				FILE_WARNING_FLAGS += -Wno-unused-private-field

TARGET_E                      = ThorsWidgets.slib
TARGET						= display.app
CXXFLAGS					+= $(SDL_CFLAGS)
LDLIBS						+= $(SDL_LIBS)
LINK_LIBS					+= ThorsSDL

UNITTEST_LINK_LIBS			+= ThorsSDL

include $(THORSANVIL_ROOT)/build/tools/Makefile
