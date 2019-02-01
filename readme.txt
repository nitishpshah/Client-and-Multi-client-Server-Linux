compile using 
g++ ./singleclient_server.cpp -o singleclient_server
g++ ./multiclient_server.cpp -o multiclient_server
g++ ./client.cpp -o client

run using:
./singleclient_server port_number
./multiclient_server  port_number		
./client servers_address  port_number  

example:
./singleclient_server 5000
./multiclient_server  5000
./client 10.250.1.500 5000

