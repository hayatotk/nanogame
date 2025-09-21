CXX := g++
CXXFLAGS := -Wall -O2 -std=c++17
LDFLAGS := -lSDL2 -lSDL2_ttf

SRC := $(wildcard src/*.cpp)
OBJ := $(patsubst src/%.cpp,out/%.o,$(SRC))
BIN := test

all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

out/%.o: src/%.cpp | out
	$(CXX) $(CXXFLAGS) -c $< -o $@

out:
	mkdir -p out

clean:
	rm -f $(OBJ) $(BIN)
