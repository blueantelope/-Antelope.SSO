include config

.PHONY: clean

test_common: init
	@echo "compile test_common"
	$(CXX) $(CFLAGS) test_common.cpp -o $(TARGET)/test_common

test_ini_reader : init
	@echo "compile test_ini_reader"
	$(CXX) $(CFLAGS) test_ini_reader.cpp $(SRC_DIR)/ini_reader.cpp -o $(TARGET)/test_ini_reader

init :
	mkdir -p $(TARGET)
clean :
	$(RM) -r $(TARGET)
