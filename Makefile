IDIR=sbg-checkout
SDIR=sbg-checkout
ODIR=obj

CXX=g++
AR=ar
CXXFLAGS=-c -Wall -Wextra -std=c++14 -Wno-unused-parameter -Wno-unused-variable -D_FILE_OFFSET_BITS=64
CPPFLAGS=-I$(IDIR)

HEADERS=$(wildcard $(IDIR)/*.h) $(wildcard $(IDIR)/*.hpp)
SOURCES=$(wildcard $(SDIR)/*.cpp)
OBJECTS=$(addprefix obj/, $(notdir $(SOURCES:.cpp=.o)))

# A directory creation utility
create_output_dir=@mkdir -p $(@D)

out/sbg-checkout: $(OBJECTS)
	$(create_output_dir)
	$(CXX) $(LDFLAGS) $^ -o $@ $(LIBS)
	@ cp $(SDIR)/*.json out/

$(OBJECTS): $(ODIR)/%.o: $(SDIR)/%.cpp
	$(create_output_dir)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -rf $(ODIR)
	rm -rf out/
