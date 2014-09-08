include config

.PHONY: clean

test_usermap : init usermap.o test_usermap.o
	@echo "generate test_usermap"
	$(CXX) $(TMP)/usermap.o $(TMP)/test_usermap.o -o $(TMP)/test_usermap

test_usermap.o : test_usermap.cpp
	@echo "compile test_usermap"
	$(CXX) $(CFLAGS) -o $(TMP)/test_usermap.o -c test_usermap.cpp

test_blocking_queue : init blocking_queue.o test_blocking_queue.o
	@echo "generate test_blocking_queue"
	$(CXX) $(TMP)/blocking_queue.o $(TMP)/test_blocking_queue.o -o $(TMP)/test_blocking_queue

test_blocking_queue.o : test_blocking_queue.cpp
	echo "compile test_blocking_queue"
	$(CXX) $(CFLAGS) -o $(TMP)/test_blocking_queue.o -c test_blocking_queue.cpp -lpthread

test_server_packet : init common.o ini_reader.o server.o test_server_packet.o
	@echo "generate test_server_packet"
	$(CXX) $(TMP)/common.o $(TMP)/ini_reader.o $(TMP)/server.o $(TMP)/test_server_packet.o -o $(TARGET)/test_server_packet

test_server_packet.o : test_server_packet.cpp
	@echo "compile test_server_packet"
	$(CXX) $(CFLAGS) -o $(TMP)/test_server_packet.o -c test_server_packet.cpp

test_server : init common.o ini_reader.o server.o test_server.o
	@echo "generate test_server"
	$(CXX) $(TMP)/common.o $(TMP)/ini_reader.o $(TMP)/server.o $(TMP)/test_server.o -o $(TARGET)/test_server

test_server.o : test_server.cpp
	@echo "compile test_server"
	$(CXX) $(CFLAGS) -o $(TMP)/test_server.o -c test_server.cpp

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

usermap.o : $(SRC_DIR)/usermap.cpp
	@echo "compile usermap.o"
	$(CXX) $(CFLAGS) -o $(TMP)/usermap.o -c $(SRC_DIR)/usermap.cpp

blocking_queue.o : $(SRC_DIR)/blocking_queue.cpp
	@echo "compile blocking_queue.o"
	$(CXX) $(CFLAGS) -o $(TMP)/blocking_queue.o -c $(SRC_DIR)/blocking_queue.cpp -lpthread

server.o : $(SRC_DIR)/server.cpp
	@echo "compile server.o"
	$(CXX) $(CFLAGS) -o $(TMP)/server.o -c $(SRC_DIR)/server.cpp

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
