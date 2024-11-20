SRC_DIR := .
OBJ_DIR := .
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
LDFLAGS := -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system
CPPFLAGS := -g -Wall -fpermissive -std=c++17
CXXFLAGS := -I/opt/homebrew/include
TARGET := game.out

$(TARGET): $(OBJ_FILES)
	g++ -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

run:
	./$(TARGET)

clean:
	rm $(TARGET) *.o
