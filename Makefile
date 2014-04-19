include config

.PHONY : clean

all : init


init :
	mkdir -p $(TARGET)

clean :
	$(RM) -r $(TARGET) $(BULDIR)
