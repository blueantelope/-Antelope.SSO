include config

.PHONY : clean

all : init common.o ini_reader.o blocking_queue.o thread_pool.o server.o main.o
	@echo "generate antelopeSSO"
	$(CXX) $(TMP)/common.o $(TMP)/ini_reader.o $(TMP)/blocking_queue.o $(TMP)/thread_pool.o $(TMP)/server.o $(TMP)/main.o -o $(TARGET)/antelopeSSO

main.o : $(SRC_DIR)/main.cpp
	@echo "compile main.o"
	$(CXX) $(CFLAGS) -o $(TMP)/main.o -c $(SRC_DIR)/main.cpp

server.o : $(SRC_DIR)/server.cpp
	@echo "compile server.o"
	$(CXX) $(CFLAGS) -o $(TMP)/server.o -c $(SRC_DIR)/server.cpp

thread_pool.o : $(SRC_DIR)/thread_pool.cpp
	@echo "compile thread_pool.o"
	$(CXX) $(CFLAGS) -o $(TMP)/thread_pool.o -c $(SRC_DIR)/thread_pool.cpp

blocking_queue.o : $(SRC_DIR)/blocking_queue.cpp
	@echo "compile blocking_queue.o"
	$(CXX) $(CFLAGS) -o $(TMP)/blocking_queue.o -c $(SRC_DIR)/blocking_queue.cpp

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
