#Email: gunrhxcd2001@gmail.com

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -pedantic -g

SRC = Game.cpp Player.cpp Governor.cpp Spy.cpp Baron.cpp General.cpp Judge.cpp Merchant.cpp RoleFactory.cpp
OBJ = $(SRC:.cpp=.o)

MAIN = Main
TEST = test

all: $(MAIN) $(TEST)

# קובץ ההדגמה הראשי
$(MAIN): main.cpp $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lsfml-graphics -lsfml-window -lsfml-system

# קובץ הבדיקות
$(TEST): tests.cpp $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# בדיקת זליגות זיכרון
valgrind: $(MAIN)
	valgrind --leak-check=full ./$(MAIN)

# ניקוי קבצים
clean:
	rm -f *.o $(MAIN) $(TEST)
