# Variables
CXX = g++
CXXFLAGS = -std=c++11 -Wall -g
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
EXEC = monopoly
TEST_EXEC = test_monopoly

# Source and Header Files
SOURCES = main.cpp Player.cpp Board.cpp Dice.cpp StreetSquare.cpp RailroadSquare.cpp UtilitySquare.cpp PropertySquare.cpp ChanceSquare.cpp CommunityChestSquare.cpp Card.cpp GameController.cpp Square.cpp SpecialSquare.cpp
HEADERS = Player.hpp Board.hpp Dice.hpp StreetSquare.hpp RailroadSquare.hpp UtilitySquare.hpp PropertySquare.hpp ChanceSquare.hpp CommunityChestSquare.hpp Card.hpp GameController.hpp Square.hpp SpecialSquare.hpp
OBJECTS = $(SOURCES:.cpp=.o)

# Test Source File
TEST_SOURCES = test.cpp
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

# Default Target
all: $(EXEC)

# Game build
$(EXEC): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(EXEC) $(LDFLAGS)

# Test build
test: $(TEST_OBJECTS) $(filter-out main.o, $(OBJECTS))
	$(CXX) $(TEST_OBJECTS) $(filter-out main.o, $(OBJECTS)) -o $(TEST_EXEC) $(LDFLAGS)

# Compile source files into object files, ensuring dependency on header files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJECTS) $(TEST_OBJECTS) $(EXEC) $(TEST_EXEC)

# Run the game
run: $(EXEC)
	./$(EXEC)

# Run the tests
test_run: $(TEST_EXEC)
	./$(TEST_EXEC)
