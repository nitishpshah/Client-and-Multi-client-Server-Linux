
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
using namespace std;

/*
	TODO#1 : make function for building the address structure
	and transfer functions to other file that will be included in both client and server
*/

//forward function declarations
int string_to_integer(string s);
string to_upper(char[]);

int main(int argc, char* argv[]){
	if(argc == 1){
		cout<<"use as ./server port_number"<<endl;
		return 0;
	}

	string str_port = argv[1];
	int PORT = string_to_integer(str_port);
	const int BACKLOG = 10;

	//make socket_address structures
	int sockfd, new_fd;		//sockfd for listening socket, new_fd for connection with client socket
	socklen_t sin_size;		//for use in binding
	struct sockaddr_in my_addr, their_addr;	//their_addr is the clients' addresses
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(PORT);	//host to network byte order
	//converts a string containing an IPv4 dotted-decimal address into a proper address for the IN_ADDR structure.
	//my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	my_addr.sin_addr.s_addr = INADDR_ANY;
	//set the rest 8 its to zero
	//signature: void * memset ( void * ptr, int value, size_t num );
	memset(&(my_addr.sin_zero), '\0', 8);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);		//TCP
	if(sockfd == -1){
		cout<< "couldn't make socket"<<endl;
	}
	
	//and bind it to address
	int bin  = bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr));
	if(bin == -1){
		cout<< "binding error"<<endl;
		close(sockfd);
		return -1;
	}

	//listen on the listening socket for connection requests
	if (listen(sockfd, BACKLOG) == -1){
		cout<<"listening error"<<endl;
		close(sockfd);
		return -1;
	}
	cout<<"ready to accept connections"<<endl;
	new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
	cout<<"connected to client "<<their_addr.sin_addr.s_addr<<endl;
	const int MAXDATASIZE = 1024;
	string send_this;
	char buff[MAXDATASIZE];	//buffer
	while(1){
		//set buffer to zero
		memset(&buff[0], '\0', MAXDATASIZE);	 
		int numbytes = recv(new_fd, buff, MAXDATASIZE-1, 0);
		if(numbytes>0){
				cout<<"Message from "<<new_fd<<": "<<buff<<endl;
			send_this = to_upper(buff);
				int sen = send(new_fd, &send_this[0], numbytes, 0);	
				cout<<"Replied to"<<new_fd<<": "<<send_this<<endl;
			if((string)buff == "BYE"){
					break;
			}
		}
	}
	cout<<"connection closed by "<<new_fd<<endl;
	close(new_fd);
	close(sockfd);
}


int string_to_integer(string s)
{
	int res = 0;
	int pow = 10;
	for (int i = 0; i < s.length(); ++i)
	{
		if(s[i]=='0'){res = res*pow + 0;}
		else if(s[i]=='1'){res = res*pow+1;}
		else if(s[i]=='2'){res = res*pow+2;}
		else if(s[i]=='3'){res = res*pow+3;}
		else if(s[i]=='4'){res = res*pow+4;}
		else if(s[i]=='5'){res = res*pow+5;}
		else if(s[i]=='6'){res = res*pow+6;}
		else if(s[i]=='7'){res = res*pow+7;}
		else if(s[i]=='8'){res = res*pow+8;}
		else if(s[i]=='9'){res = res*pow+9;}
	}
	return res;
}

string to_upper(char s[]){
	// returns string with each character in upper case
	// ASCII values
	// 'A' = 65 'Z' = 90
	// 'a' = 97 'z' = 122
	string ret;
	for (int i = 0; i < strlen(s); ++i)
	{
		if( s[i] <= 122 && s[i] >= 97){
			s[i] = char( s[i] - 97 + 65 );  
		}
		ret += s[i];
	}
	return ret;
}
