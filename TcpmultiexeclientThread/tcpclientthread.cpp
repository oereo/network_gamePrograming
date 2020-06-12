#include <stdio.h>
#include <WinSock2.h>

#define MAX_CLIENT 1
#define MAX_MESSAGE 1


DWORD WINAPI NetReceive(LPVOID socketConnect)
{
	char recvBuffer[127];
	int RecvBytes;

	while (1) {
		RecvBytes = ::recv((SOCKET)socketConnect, recvBuffer, 126, 0);
		if (RecvBytes < 1)
			break;
		printf("RECV %d> %d bytes: %s\n", socketConnect, RecvBytes, recvBuffer);

		if (recvBuffer[RecvBytes - 2] == '!')
			break;
	}
	return NULL;
}


void main()
{
	WSADATA wsaData;
	SOCKET socketConnect[MAX_CLIENT];
	struct sockaddr_in serverAddr;
	int  k;
	HANDLE handleThread[MAX_CLIENT];


	::WSAStartup( 0x202, &wsaData );

	for(k=0;k<MAX_CLIENT;k++){
		socketConnect[k] = INVALID_SOCKET;
		socketConnect[k] = ::socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
		if( socketConnect[k] == INVALID_SOCKET )
		{
			printf( "Cannot create socket %d !!\n", k);
			continue;
		}
	}

	//  접속할 서버의 정보를 설정한다.
	::memset( &serverAddr, 0, sizeof( serverAddr ) );
	serverAddr.sin_family		= AF_INET;
	serverAddr.sin_addr.s_addr	= ::inet_addr( "210.89.160.88" ); //::htonl(INADDR_LOOPBACK); "127.0.0.1"
	serverAddr.sin_port			= ::htons( 80 );//8600 

	for(k=0;k<MAX_CLIENT;k++){
		if( socketConnect[k] != INVALID_SOCKET){
			if(::connect( socketConnect[k], ( struct sockaddr* )&serverAddr, sizeof( serverAddr ) ) == SOCKET_ERROR )
			{
				printf( "Cannot connect to server %d !!\n", k);
				socketConnect[k] = INVALID_SOCKET;
				continue;
			}
			else{
// create thread for receive packets
				handleThread[k] = CreateThread(NULL, 0, NetReceive, (void*)socketConnect[k], THREAD_PRIORITY_NORMAL, NULL);

			}
		}
	}



	//  서버와 통신을 한다.
	int count=0;
	while(count++ < MAX_MESSAGE){
		char sendBuffer[127];
		int sentBytes;

		char recvBuffer[127];
		int  RecvBytes=0;


		for(k=0;k<MAX_CLIENT;k++){

			if(socketConnect[k] != INVALID_SOCKET){
				sprintf(sendBuffer, "%d> Test \n\n", k); //%d> Test Message to server
				if(count==MAX_MESSAGE)
					strcat(sendBuffer, "!");

				sentBytes = ::send( socketConnect[k], sendBuffer, ::strlen( sendBuffer ) + 1, 0 );
				if(sentBytes<0){
					::shutdown( socketConnect[k], SD_BOTH );
					::closesocket( socketConnect[k] );
					socketConnect[k]=INVALID_SOCKET;
				}
				else{
					printf( "SND %d> Test.\n\n", k ); //"%d> %d Test.\n\n", k, sentBytes 


				}
			}
		}

//		Sleep(200);
	}

// close main() and threads gracefully using ::WaitForMultipleObjects()
	::WaitForMultipleObjects(MAX_CLIENT, handleThread, TRUE, INFINITE);

	for(k=0;k<MAX_CLIENT;k++){
		::shutdown( socketConnect[k], SD_BOTH );
		::closesocket( socketConnect[k] );
	}
	::WSACleanup();

	printf("Server Connection Closed !\n");
	char temp[120];
	fgets(temp, 119, stdin);
}
