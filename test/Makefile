include config

.PHONY: clean

test_ini_reader : init
	@echo "compile test_ini_reader"
	$(CXX) $(CFLAGS) test_ini_reader.cpp $(SRC_DIR)/ini_reader.cpp -o $(TARGET)/test_ini_reader

init :
	mkdir -p $(TARGET)
clean :
	$(RM) -r $(TARGET)
