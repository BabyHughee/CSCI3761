CC=g++
LD=g++
CC_FLAGS=-g -std=c++11
CLIENT= client.o # implementations.o
SERVER= server.o # implementation.o
SOB= server
COB= client

all: $(CLIENT) $(SERVER)
	$(LD) -o $(COB) $(CLIENT)
	$(LD) -o $(SOB) $(SERVER)

client: $(CLIENT)
	$(LD) -o $(COB) $(CLIENT)

server: $(SERVER)
	$(LD) -o $(SOB) $(SERVER)

test:
	g++ test.cpp -o TEST

clean:
	rm -rf $(SERVER) $(CLIENT) $(COB) $(SOB) TEST

%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@
