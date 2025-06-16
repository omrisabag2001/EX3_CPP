CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -pedantic

# wxWidgets configuration
WX_PATH = /opt/homebrew/opt/wxwidgets
WX_VERSION = osx-cocoa-unicode-3.2
WX_INC = -I$(WX_PATH)/include -I$(WX_PATH)/lib/wx/include/$(WX_VERSION)
WX_LIB = -L$(WX_PATH)/lib -lwx_osx_cocoau_core-3.2 -lwx_baseu-3.2 \
         -framework Cocoa -framework IOKit -framework Carbon

# Sources and headers
SRC = Game.cpp Player.cpp Governor.cpp Spy.cpp Baron.cpp General.cpp Judge.cpp Merchant.cpp RoleFactory.cpp
HEADERS = Game.hpp Player.hpp Governor.hpp Spy.hpp Baron.hpp General.hpp Judge.hpp Merchant.hpp RoleFactory.hpp
OBJS = $(SRC:.cpp=.o)

# Targets
all: Main

Main: $(OBJS) Demo.cpp
	$(CXX) $(CXXFLAGS) $(SRC) Demo.cpp -o Main

test: $(OBJS) tests.cpp
	$(CXX) $(CXXFLAGS) $(SRC) tests.cpp -o tests
	./tests

wxgui: $(OBJS) GUI.cpp
	$(CXX) $(CXXFLAGS) $(WX_INC) $(SRC) GUI.cpp $(WX_LIB) -o gui_app

valgrind: test
	valgrind --leak-check=full ./test.out

clean:
	rm -f *.o *.out Main tests gui_app
