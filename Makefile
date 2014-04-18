
CC		=gcc
CFLAGS		=-I.

SRCDIR		=src
TARGET		=bin
INCDIR		=include
BULDIR		=build

.PHONY : clean

all :

clean :
	$(RM) -r $(TARGET) $(BULDIR)
