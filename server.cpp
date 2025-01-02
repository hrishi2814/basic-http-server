// C++ program to show the example of server application in
// socket programming
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <regex>
#include<fstream>
#include<streambuf>
using namespace std;

int rexparse(const char* buffer,string &reqtype,string &path){
	//regular expression for matching first line like - "GET /index.html HTTP/1.1" ---just an example 
	std::regex pattern(R"((GET|POST|DELETE|PUT)\s+/(\S+)\s+(HTTP/\d\.\d))");

	
	std::cmatch matches; //dont use smatch for matching char* lmao
	if(std::regex_search(buffer,matches,pattern)){            //using regex_search is better than match which is strict
		//cout<< "Request Type:"<<matches[1]<<endl;
		reqtype = matches[1].str();
		//cout<< "Address: "<<matches[2]<<endl;
		path = matches[2].str();
		//cout<< "HTTP version:"<<matches[3]<<endl;
		return 1;
		}

	return 0;
}
int serveFile(const string& path,int clientSocket){
	std::ifstream file(path);
	if(file.is_open()){
		//reading file contents and then sending
		std::string fileContent((std::istreambuf_iterator<char>(file)),std::istreambuf_iterator<char>());

		//response for sending with header and content type
		std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n"+fileContent;

		//sending the damn response
		send(clientSocket,response.c_str(),response.length(),0);
	}
	else{
		//file not found , 404
		const char* response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nFile not Found";
		send(clientSocket,response,strlen(response),0);
	}
}

int main()
{
    // creating socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSocket==-1){
	cout<<"Socket creation Failed!"<<endl;
    }

    // specifying the address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(4561);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // binding socket.
    if(bind(serverSocket, (struct sockaddr*)&serverAddress,sizeof(serverAddress))<0){
	cerr<<"Binding Failed!"<<endl;
	return -1;
    }

    // listening to the assigned socket
    if(listen(serverSocket, 5)<0){
	cerr<<"Listen Failed!"<<endl;
	close(serverSocket);
	return -1;
    };

    char buffer[1024] = {0};
    while(true){
    // accepting connection request
	int clientSocket = accept(serverSocket, nullptr, nullptr);
	if(clientSocket<0){
		cerr<<"Accept Failed!"<<endl;
		close(clientSocket);
		return -1;
	}

    // recieving data
   	 //char buffer[1024] = { 0 };
    	 int bytes_recvd = recv(clientSocket, buffer, sizeof(buffer), 0);
	 if(bytes_recvd<0){
		cerr<<"Failed to receive!"<<endl;
		close(clientSocket);
		return -1;
	 }

	 //null terminate the string
	 buffer[bytes_recvd] = '\0';
	 
	 //printing the received buffer
	 cout << buffer<< endl;
    	 
	 std::string req_type;
	 std::string file;


	 //parsing the buffer
	 if(rexparse(buffer,req_type,file)==1){
		cout<<"Got a request and it was parsed!Above is the info"<<"this is the req="<<req_type<<"file requested"<<file<<endl;
	 }
	
	 if(req_type=="GET"){
	 serveFile(file,clientSocket);
	 }
	 if(file==""){
		const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nOK";
		send(clientSocket,response,strlen(response),0);
	 }
	 //drafting a response to send
	 //const char *response = "HTTP/1.1 200 OK\r\n";
         
	 //const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello, world!";	 
	 
	 //send(clientSocket, response, strlen(response) , 0);
	 //cout<<req_type<<file<<endl;	 
	 //if(sentBytes<0){cout<"Sending Failed!"<<endl;}
	 //closing client socket after processing request
	 
	 close(clientSocket);
    }
   
    return 0;
}

