COMPILATEUR=gcc
EXEC=exec
SRC=src/main
CLIENT=src/Client/client
SERVER=src/Server/server
MSG=src/Message/message
PROTOCOL=src/Protocol/protocol
GLOBAL=src/global
	


all: main clean

main: main.o client.o server.o message.o protocol.o
	gcc *.o -o $(EXEC)

main.o: $(SRC).c $(CLIENT).h $(SERVER).h
	gcc -g -Wall -c $(SRC).c


server.o: $(SERVER).c $(SERVER).h $(GLOBAL).h $(MSG).h $(PROTOCOL).h
	gcc -g -Wall -c $(SERVER).c

client.o: $(CLIENT).c $(CLIENT).h $(GLOBAL).h $(MSG).h $(PROTOCOL).h
	gcc -g -Wall -c $(CLIENT).c


message.o: $(MSG).c $(MSG).h $(GLOBAL).h
	gcc -g -Wall -c $(MSG).c
	
protocol.o: $(PROTOCOL).c $(PROTOCOL).h $(GLOBAL).h
	gcc -g -Wall -c $(PROTOCOL).c

clean:
	rm -rf *.o


