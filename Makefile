CXX			= g++
CXXFLAGS	= -O2 -Werror -Wall -Wextra -Wpedantic -std=c++17 \
	-I./include \
	-Wno-unused-function -Wno-unused-parameter -Wno-unused-variable \
	-Wno-format-nonliteral \
	-Wformat=2 -Wformat-security \
	-Wnull-dereference -Wstack-protector -Wtrampolines -Wvla \
	-Warray-bounds=2 \
	-Wshift-overflow=2 \
	-Wlogical-op -Wduplicated-cond \
	-Wformat-signedness -Wshadow -Wstrict-overflow=4 \
	-Wundef -Wswitch-enum \
	-Wstack-usage=10000 \
	-D_FORTIFY_SOURCE=2 

# Could be added for wxwidget > 3.0	
#-Wcast-qual  -Wconversion \

# Could be added for recent compilers
#-fstack-protector-strong -fPIE -fsanitize=address \
#-fsanitize=leak -fno-omit-frame-pointer -fsanitize=undefined \
#-fsanitize=bounds-strict -fsanitize=float-divide-by-zero \
#-fsanitize=float-cast-overflow

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
	@doxygen $(DOC)/wxtest.conf

.PHONY: cleandoc
cleandoc:
	@rm -rf $(DOC)/html
	@echo "clean doc done"

.PHONY: clean
clean:
	@rm -rf $(TARGET) $(OBJECTS)
	@echo "clean done"

.PHONY: check
check:
	@cppcheck -I./include \
		--check-config \
		--enable=all \
		--std=c++11 \
		--suppress=missingIncludeSystem \
		$(SRC)	

