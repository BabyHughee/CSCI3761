CC=g++
LD=g++
CC_FLAGS= -g -std=c++11
OBJECTS= kaestLab3.o kaestLab3_main.o
TEST= test.o implementation.o
OB= kae2414
BINARY=MST

all: $(OBJECTS) #docs
	$(LD) -o $(BINARY) $(OBJECTS)

test: $(TEST) test.o
	$(LD) -o test $(TEST) test.o

clean:
	rm -rf $(OBJECTS) $(TEST) $(BINARY) html latex $(OB).zip test test.o def docbook man rtf

%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

docs:
	doxygen doxygen.cfg

zip:
	zip -r $(OB).tar *.cpp *.h *.pdf README makefile # *.txt *.csv
	cp $(OB).tar ~/Desktop/
	#cp -f $(OB).zip ~/kaest/CSCI3761/completeZips
