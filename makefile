
CXX = g++

CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g

LDFLAGS =

EXECUTABLE := play_game

SRCS := $(filter-out ./game_main.cpp, $(shell find ./ -type f ! -wholename "*examples/*" -name "*.cpp"))
HEADERS := $(shell find ./ -type f ! -wholename "*examples/*" -name "*.hpp*")
OBJS := $(SRCS:.cpp=.o)

main: $(OBJS) $(HEADERS) game_main
	$(CXX) $(LDFLAGS) $(OBJS) game_main.o -o $(EXECUTABLE)

game_main: $(OBJS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -c game_main.cpp -o game_main.o
	
$(OBJS): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
	
clean:
	@rm -vf $(OBJS)
	@rm -vf $(EXECUTABLE)
	@echo All object files and executable removed
	
display:
	@echo Headers:
	@echo $(HEADERS)

	@echo Sources:
	@echo $(SRCS)
	
	@echo Objects:
	@echo $(OBJS)
	
	@echo Executable:
	@echo $(EXECUTABLE)

PHYSICS_TEST_SRCS := $(shell find ./examples/physics_test/ -type f -name "*.cpp")
PHYSICS_TEST_OBJS := $(PHYSICS_TEST_SRCS:.cpp=.o)
PHYSICS_TEST_HEADERS := $(shell find ./examples/physics_test/ -type f -name "*.hpp")
physics_test: $(OBJS) $(HEADERS) $(PHYSICS_TEST_OBJS) $(PHYSICS_TEST_HEADERS)
	$(CXX) $(LDFLAGS) $(OBJS) $(PHYSICS_TEST_OBJS) -o ./examples/physics_test/physics_test

$(PHYSICS_TEST_OBJS): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@