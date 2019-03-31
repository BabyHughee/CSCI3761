CC=g++
LD=g++
CC_FLAGS=-g -std=c++11
CLIENT= client.o # implementations.o
SERVER= server.o # implementation.o
SOB= SERVER
COB= CLIENT

all: $(CLIENT) $(SERVER)
	$(LD) -o $(COB) $(CLIENT)
	$(LD) -o $(SOB) $(SERVER)

client: $(CLIENT)
	$(LD) -o $(COB) $(CLIENT)

server: $(SERVER)
	$(LD) -o $(SOB) $(SERVER)

clean:
	rm -rf $(SERVER) $(CLIENT) $(COB) $(SOB)

%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@
