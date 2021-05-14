.PHONY:all
all:udpClient udpServer
udpClient:udpClient.cc
	g++ -o $@ $^ -std=c++11
udpServer:udpServer.cc
	g++ -o $@ $^ 
.PHONY:clean
clean:
	rm -f udpClient udpServer 
