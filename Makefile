
CC		=gcc
CFLAGS		=-I.

SRCDIR		=src
TARGET		=bin
INCDIR		=include

.PHONY : clean

all :

clean :
	$(RM) -r $(TARGET) 
