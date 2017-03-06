
CXX = g++

CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g

LDFLAGS =

SRCS := $(shell find ./ -type f -name "*.cpp")
HEADERS := $(shell find ./ -type f -name "*.hpp*")
OBJS := $(SRCS:.cpp=.o)

EXECUTABLE = main

main: $(OBJS) $(HEADERS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $(EXECUTABLE)

$(OBJS): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -f $(EXECUTABLE)
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
