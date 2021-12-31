CXX			= g++
CXXFLAGS	= -g -Werror -Wall -Wextra -Wpedantic -std=c++17 -I./include \
	-Wno-unused-function -Wno-unused-parameter -Wno-unused-variable
LDFLAGS		= -g -s
LDLIBS		= -lm -lmosquittopp

CXXFLAGS += $(shell wx-config --cxxflags)
LDFLAGS  += $(shell wx-config --libs std)

DOC			= doc
SRC			= src
CPPW		= *.cpp
TARGET     	= wxtest
SRC_FILES 	= $(wildcard $(SRC)/$(CPPW)) $(wildcard$(SRC)/**/$(CPPW))
OBJECTS 	= $(SRC_FILES:%.cpp=%.o)

.SUFFIXES = 

.PHONY: all

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

.PHONY: doc
doc:
	doxygen $(DOC)/wxtest.conf

.PHONY: cleandoc
cleandoc:
	rm -rf $(DOC)/html	

.PHONY: clean
clean:
	rm -rf $(TARGET) $(OBJECTS)  

.PHONY: check
check:
	cppcheck -I./include \
		--check-config \
		--enable=all \
		--std=c++11 \
		--suppress=missingIncludeSystem \
		$(SRC) -I $(SRC)	

