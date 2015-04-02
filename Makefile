SRCS = \
	main.c

OBJS = $(subst .c,.o,$(SRCS))

CFLAGS = 
LIBS = 
TARGET = c-funchain

all : $(TARGET)

$(TARGET) : $(OBJS)
	gcc -o $@ $(OBJS) $(LIBS)

.c.o :
	gcc -c $(CFLAGS) -I. $< -o $@

clean :
	rm -f *.o $(TARGET)
