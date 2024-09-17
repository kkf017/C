COMPILATEUR=gcc
EXEC=exec
SRC=src/main
CLIENT=src/Client/client
SERVER=src/Server/server
MSG=src/Message/message

	


all: main clean

main: main.o client.o server.o message.o
	gcc *.o -o $(EXEC)

main.o: $(SRC).c $(CLIENT).h $(SERVER).h
	gcc -g -Wall -c $(SRC).c


server.o: $(SERVER).c $(SERVER).h $(MSG).h
	gcc -g -Wall -c $(SERVER).c

client.o: $(CLIENT).c $(CLIENT).h $(MSG).h
	gcc -g -Wall -c $(CLIENT).c


message.o: $(MSG).c $(MSG).h
	gcc -g -Wall -c $(MSG).c

clean:
	rm -rf *.o


