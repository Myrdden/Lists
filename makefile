.SUFFIXES : .cpp

CC = g++

CXXFLAGS = -g -std=c++11

#.cpp's only you numpty
OBJS = test.o

TARGET = test

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

.cpp.o:
	$(CC) -c $(CXXFLAGS) $(INCDIR) $<

clean:
	rm -f $(OBJS) $(TARGET) core
