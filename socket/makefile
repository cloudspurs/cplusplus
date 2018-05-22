all:server client


server:server.cpp
	g++ $< -std=c++11 -pthread -o $@

client:client.cpp
	g++ $< -o $@


.PHONY:clean
clean:
	rm -f server
	rm -f client
