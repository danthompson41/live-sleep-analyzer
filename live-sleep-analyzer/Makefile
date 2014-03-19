CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		live-sleep-analyzer.o

LIBS =

TARGET =	live-sleep-analyzer.exe

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
