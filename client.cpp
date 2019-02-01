
#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
using namespace std;

//forward function declarations
int string_to_integer(string s);

int main(int argc, char* argv[]){
	if(argc != 3){
		cout<<"use as: client ip_address_of_server port_number"<<endl;
		return -1;
	}
	string str_port = argv[2];
	int PORT = string_to_integer(str_port);
	int sockfd;

	//prepare structure for socket data
	struct sockaddr_in server_addr;		
	server_addr.sin_family = AF_INET;	//address family
	server_addr.sin_port = htons(PORT);	//host to network short (byte order)
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);	
	//converts a string containing an IPv4 dotted-decimal address into a proper address for the IN_ADDR structure.
	//set the rest 8 its to zero
	//signature: void * memset ( void * ptr, int value, size_t num );
	memset(&(server_addr.sin_zero), '\0', 8);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);		//TCP
	
	if(sockfd == -1){
		cout<< "error, cannot make socket"<<endl;
		return -1;
	}
	
	//connect to server using the sockaddr_in structure created before after casting it to sockaddr
	int x = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr));

	if(x == -1){
		cout<<"connection failed\n"<<errno<<endl;
		return -1;
	}
	
	const int MAXDATASIZE = 1024;		//buffer size
	string send_this;
	char buff[MAXDATASIZE]; //buffer for the string s recieved

	//keep prompting for sending till 'bye'
	while(1){
		//set buffer to zeros
		memset(&buff[0], '\0', MAXDATASIZE);
			cout<<"Enter message for server: ";
		getline(cin, send_this);
		int len = send_this.length();
		if(len > 0){
			//take string as input and send address of first character
			int sen = send(sockfd, &send_this[0], len, 0);	
			int nbytes = recv(sockfd, &buff[0], MAXDATASIZE-1, 0);
				cout<<"Message from server: "<<buff<<endl;
			if(send_this == "BYE" || send_this == "bye"){
				break;
			}
		}
	}
	close(sockfd);
	cout<<"connection closed"<<endl;
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
