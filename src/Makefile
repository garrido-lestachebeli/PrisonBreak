CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

SRC = main.cpp \
      GameManager.cpp \
      Map.cpp \
      Player.cpp \
      Guard.cpp \
      Exit.cpp \
      Camera.cpp \
      Tunnel.cpp \
      EmptyRoom.cpp

OUT = game

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

run: all
	./$(OUT)

clean:
	rm -f $(OUT)