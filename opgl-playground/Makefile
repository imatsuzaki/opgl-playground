CXXFLAGS = -g -Wall -std=c++11 -I/usr/local/include
LDLIBS = -L/usr/local/lib -lglfw3 -lGLEW -framework OpenGL \
        -framework CoreVideo -framework IOKit -framework Cocoa
OBJECTS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
TARGET = opgl-playground

.PHONY: clean

$(TARGET): $(OBJECTS)
	$(LINK.cc) $^ $(LOADLIBS) $(LDLIBS) -o $@

clean:
	-$(RM) $(TARGET) *~ .*~ core
