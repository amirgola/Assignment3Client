PROGRAM = TFTPclient

SRCS = 	KeyboardTask.cpp \
	SocketTask.cpp \
	MessageEncoderDecoder.cpp \
	connectionHandler.cpp \
	echoClient.cpp \
	ACKpacket.cpp \
	BCASTpacket.cpp \
	DATApacket.cpp \
	DELRQpacket.cpp \
	DIRQpacket.cpp \
	DISCpacket.cpp \
	ERRORpacket.cpp \
	LOGRQpacket.cpp \
	Packet.cpp \
	RRQpacket.cpp \
	WRQpacket.cpp \
	Protocol.cpp \

SRCDIR = src
BINDIR = bin

OBJS = $(SRCS:%.cpp=$(BINDIR)/%.o)

CC = g++

CFLAGS = -g -std=c++11 -Wall -Weffc++ -Werror
LFLAGS = -L/usr/lib

INCLUDES = -I./include -isystem /usr/include
LIBS = -lboost_locale -lboost_system -lboost_thread

.PHONY: all
all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) $(LFLAGS) -o $(BINDIR)/$(PROGRAM) $+ $(LIBS)

$(BINDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -c $(CFLAGS) $(INCLUDES) -o $@ $<

.PHONY: clean
clean:
	rm -rf $(BINDIR)/*