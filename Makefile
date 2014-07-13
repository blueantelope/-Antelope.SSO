include config

.PHONY : clean

all : init common.o ini_reader.o main.o
	@echo "generate antelopeSSO"
	$(CXX) $(TMP)/common.o $(TMP)/ini_reader.o $(TMP)/main.o -o $(TARGET)/antelopeSSO

main.o : $(SRC_DIR)/main.cpp
	@echo "compile main.o"
	$(CXX) $(CFLAGS) -o $(TMP)/main.o -c $(SRC_DIR)/main.cpp

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
