COMPILATEUR=gcc
EXEC=exec
SRC=src/main
CLIENT=src/Client/Client
SERVER=src/Server/Server
EXAMPLE=src/Example/Example

	


all: main clean

main: main.o client.o server.o example.o
	gcc *.o -o $(EXEC)

main.o: $(SRC).c $(CLIENT).h $(SERVER).h
	gcc -g -Wall -c $(SRC).c


server.o: $(SERVER).c $(SERVER).h $(EXAMPLE).h
	gcc -g -Wall -c $(SERVER).c

client.o: $(CLIENT).c $(CLIENT).h $(EXAMPLE).h
	gcc -g -Wall -c $(CLIENT).c


example.o: $(EXAMPLE).c $(EXAMPLE).h
	gcc -g -Wall -c $(EXAMPLE).c

clean:
	rm -rf *.o


