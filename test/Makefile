include config

.PHONY: clean

test_blocking_queue : init blocking_queue.o test_blocking_queue.o
	@echo "generate test_blocking_queue"
	$(CXX) $(TMP)/blocking_queue.o $(TMP)/test_blocking_queue.o -o $(TMP)/test_blocking_queue

test_blocking_queue.o : test_blocking_queue.cpp
	echo "compile test_blocking_queue"
	$(CXX) $(CFLAGS) -o $(TMP)/test_blocking_queue.o -c test_blocking_queue.cpp -lpthread

test_ini_reader : init common.o ini_reader.o test_ini_reader.o
	@echo "generate test_ini_reader"
	$(CXX) $(TMP)/common.o $(TMP)/ini_reader.o $(TMP)/test_ini_reader.o -o $(TARGET)/test_ini_reader

test_ini_reader.o : test_ini_reader.cpp
	@echo "compile test_ini_reader"
	$(CXX) $(CFLAGS) -o $(TMP)/test_ini_reader.o -c test_ini_reader.cpp

test_common : init common.o test_common.o
	@echo "generate test_common"
	$(CXX) $(TMP)/common.o $(TMP)/test_common.o -o $(TARGET)/test_common

test_common.o : test_common.cpp
	@echo "compile test_common"
	$(CXX) $(CFLAGS) -o $(TMP)/test_common.o -c test_common.cpp

blocking_queue.o : $(SRC_DIR)/blocking_queue.cpp
	@echo "compile blocking_queue.o"
	$(CXX) $(CFLAGS) -o $(TMP)/blocking_queue.o -c $(SRC_DIR)/blocking_queue.cpp -lpthread

ini_reader.o : $(SRC_DIR)/ini_reader.cpp
	@echo "compile ini_reader.o"
	$(CXX) $(CFLAGS) -o $(TMP)/ini_reader.o -c $(SRC_DIR)/ini_reader.cpp

common.o : $(SRC_DIR)/common.cpp
	@echo "compile common.o"
	$(CXX) $(CFLAGS) -o $(TMP)/common.o -c $(SRC_DIR)/common.cpp

init :
	mkdir -p $(TARGET)
	mkdir -p $(TMP)

clean :
	$(RM) -r $(TARGET) $(TMP)
