CC=g++
LD=g++
CC_FLAGS=-g -std=c++11
OBJECTS= client.o # implementations.o
SERVER= server.o # implementation.o
OB= SERVER
BINARY=

client: $(OBJECTS)
	$(LD) -o client $(OBJECTS)

server: $(SERVER)
	$(LD) -o server $(SERVER)

clean:
	rm -rf $(OBJECTS) $(SERVER) $(BINARY) html latex $(OB).zip client server server.o def docbook man rtf

%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@

docs:
	doxygen doxygen.cfg

# zip:
# 	zip -r $(OB).zip *.cpp *.h *.txt *.csv *.pdf README makefile
# 	cp $(OB).zip ~/Desktop/
# 	cp -f $(OB).zip ~/kaest/CSCI2421/completeZips
