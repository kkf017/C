COMPILATEUR=gcc
EXEC=exec
SRC=src/main
CLIENT=src/Client/client
SERVER=src/Server/server
FILES=src/Files/files

	


all: main clean

main: main.o client.o server.o files.o
	gcc *.o -o $(EXEC)

main.o: $(SRC).c $(CLIENT).h $(SERVER).h
	gcc -g -Wall -c $(SRC).c


server.o: $(SERVER).c $(SERVER).h $(FILES).h
	gcc -g -Wall -c $(SERVER).c

client.o: $(CLIENT).c $(CLIENT).h $(FILES).h
	gcc -g -Wall -c $(CLIENT).c


files.o: $(FILES).c $(FILES).h
	gcc -g -Wall -c $(FILES).c

clean:
	rm -rf *.o


