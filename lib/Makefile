AXE=..

include $(AXE)/config.mak

#LDFLAGS= -shared -fpic

OBJS= stuff.o debug.o ref.o tuple.o type.o vail.o vector.o

all: libaxe.a
libaxe.a: $(OBJS)
	ar rcs $@ $^
clean:
	$(RM) *.o libaxe.a

.PHONY: all clean
