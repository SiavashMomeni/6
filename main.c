#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <winsock2.h>
#include <ctype.h>
#include "cJSON.c"
#define SA struct sockaddr
#include <stdarg.h>
#define port 12345
#define ip "104.194.25.159"

   struct user {
        int  state;
        char  username [100];
        char  password [100];
        char * token ;
    };
    char* concat(int count, ...)
{
    va_list ap;
    int i;

    // Find required length to store merged string
    int len = 1; // room for NULL
    va_start(ap, count);
    for(i=0 ; i<count ; i++)
        len += strlen(va_arg(ap, char*));
    va_end(ap);

    // Allocate memory to concat strings
    char *merged = calloc(sizeof(char),len);
    int null_pos = 0;

    // Actually concatenate strings
    va_start(ap, count);
    for(i=0 ; i<count ; i++)
    {
        char *s = va_arg(ap, char*);
        strcpy(merged+null_pos, s);
        null_pos += strlen(s);
    }
    va_end(ap);

    return merged;
}
void reglog (struct user p1)
{

      printf("Account menu\n");
    printf("1_Register\n");
    printf("2_Login\n");
    scanf("%d", &p1.state );


    while (p1.state == 1) {
              printf("Enter  Username\n");
         scanf("%s", &p1.username) ;
         printf("Enter  Password\n") ;
         scanf("%s", &p1.password) ;
         int client_socket, server_socket;
	struct sockaddr_in servaddr, cli;
    char buffer [100] ;
	WORD wVersionRequested;
    WSADATA wsaData;
    int err;

	// Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h
    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        // Tell the user that we could not find a usable Winsock DLL.
        printf("WSAStartup failed with error: %d\n", err);
        return 1;
    }

	// Create and verify socket
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket == -1) {
		printf("Socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");

	// Assign IP and port
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(port);

	// Connect the client socket to server socket
	if (connect(client_socket, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("Connection to the server failed...\n");
		exit(0);
	}
	else
		printf("Successfully connected to the server..\n");

         memset(buffer, 0, sizeof(buffer));

         send (client_socket,concat(5 , "register " , p1.username ,", " , p1.password  ,"\n")  , 1000 , 0);
         recv(client_socket, buffer , 100, 0);
         closesocket(server_socket) ;

         cJSON * buffer_j  =cJSON_Parse( buffer ) ;
printf ("%s",cJSON_GetObjectItemCaseSensitive(buffer_j , "content") -> valuestring );
         if (strcmp(cJSON_GetObjectItemCaseSensitive(buffer_j , "type") -> valuestring ,"Error") != 0)
         {
          printf("Request Accepted\n");
          p1.state ++;
          break ;
         }
           else
            printf("Request Rejected\n");

    }


     while (p1.state == 2) {
            printf("Enter  Username\n");
            scanf("%s", &p1.username) ;
            printf("Enter  Password\n") ;
            scanf("%s", &p1.password) ;
           int client_socket, server_socket;
	struct sockaddr_in servaddr, cli;
    char buffer [100] ;
	WORD wVersionRequested;
    WSADATA wsaData;
    int err;

	// Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h
    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        // Tell the user that we could not find a usable Winsock DLL.
        printf("WSAStartup failed with error: %d\n", err);
        return 1;
    }

	// Create and verify socket
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket == -1) {
		printf("Socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");

	// Assign IP and port
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(port);

	// Connect the client socket to server socket
	if (connect(client_socket, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("Connection to the server failed...\n");
		exit(0);
	}
	else
		printf("Successfully connected to the server..\n");
            memset(buffer, 0, sizeof(buffer));
           send (client_socket, concat(5 , "login " , p1.username , ", " , p1.password , "\n" ) , 1000, 0);
           recv(client_socket, buffer , 100, 0);

             cJSON * buffer_j  =cJSON_Parse( buffer ) ;

         if (strcmp(cJSON_GetObjectItemCaseSensitive(buffer_j , "type") -> valuestring ,"Error") != 0)
         {
          printf("Request  Accepted\n");
          closesocket( server_socket ) ;
          p1.token  = cJSON_GetObjectItemCaseSensitive( buffer_j , "content") -> valuestring ;
          menu (p1) ;
          break;
         }
           else
          { closesocket( server_socket ) ;
            printf("%s \n",cJSON_GetObjectItemCaseSensitive( buffer_j , "content") -> valuestring  ) ;
          }
    }


}
void menu (struct user p1 )
{ while (true){
    printf("1_Create Channel\n");
    printf("2_Join Channel\n");
    printf("3_Log out\n");
    scanf("%d" , &p1.state) ;
    if( p1.state == 3)
    {
          int client_socket, server_socket;
	struct sockaddr_in servaddr, cli;
    char buffer [100] ;
	WORD wVersionRequested;
    WSADATA wsaData;
    int err;

	// Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h
    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        // Tell the user that we could not find a usable Winsock DLL.
        printf("WSAStartup failed with error: %d\n", err);
        return 1;
    }

	// Create and verify socket
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket == -1) {
		printf("Socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");

	// Assign IP and port
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(port);

	// Connect the client socket to server socket
	if (connect(client_socket, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("Connection to the server failed...\n");
		exit(0);
	}
	else
		printf("Successfully connected to the server..\n");

	        send(client_socket , concat(3, "logout " , p1.token, "\n") ,100, 0 ) ;
	        recv(client_socket ,buffer , 100 , 0 ) ;


	         cJSON * buffer_j  =cJSON_Parse( buffer ) ;


         if (strcmp(cJSON_GetObjectItemCaseSensitive(buffer_j , "type") -> valuestring ,"Error") != 0)
         {
          printf("Request Accepted\n");
          closesocket( server_socket ) ;
          reglog (p1) ;
          return ;

         }
           else
           {
               printf("Request Rejected\n");
            closesocket( server_socket ) ;
           }
    }

    else if (p1.state == 1)
    {
        Cchannel (p1 ) ;
       return ;
    }

       else if (p1.state == 2)
      {
          Jchannel(p1 ) ;
        return ;
      }


}
}
void Cchannel (struct user p1 )
{ while (true) {
    int client_socket, server_socket;
	struct sockaddr_in servaddr, cli;
	char buffer [100] ;

	WORD wVersionRequested;
    WSADATA wsaData;
    int err;

	// Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h
    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        // Tell the user that we could not find a usable Winsock DLL.
        printf("WSAStartup failed with error: %d\n", err);
        return 1;
    }

	// Create and verify socket
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket == -1) {
		printf("Socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");

	// Assign IP and port
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(port);

	// Connect the client socket to server socket
	if (connect(client_socket, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("Connection to the server failed...\n");
		exit(0);
	}
	else
		printf("Successfully connected to the server..\n");
    printf("Enter channel name \n");
    scanf("%s", &buffer );
    send(client_socket , concat(5 , "create channel ", buffer  , ", ", p1.token ,"\n"),100, 0);
    memset(buffer, 0, sizeof(buffer));
    recv(client_socket ,buffer ,100 , 0);
    cJSON * buffer_j  =cJSON_Parse( buffer ) ;
    printf("%s\n" ,cJSON_GetObjectItemCaseSensitive(buffer_j , "content") -> valuestring ) ;
         if (strcmp(cJSON_GetObjectItemCaseSensitive(buffer_j , "type") -> valuestring ,"Error") != 0)
         {
          printf("Request Accepted\n");
          closesocket( server_socket ) ;
          Jchannel(p1) ;

         }
           else
            printf("Request Rejected\n");
            closesocket( server_socket ) ;
    }





}
void Jchannel (struct user p1 )
{
while (true) {
        if (p1.state != 2)
            break ;
            char buffer [100];
     printf("Enter channel name you want to join \n") ;
     scanf("%s" , buffer ) ;
   int client_socket, server_socket;
	struct sockaddr_in servaddr, cli;
	WORD wVersionRequested;
    WSADATA wsaData;
    int err;

	// Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h
    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        // Tell the user that we could not find a usable Winsock DLL.
        printf("WSAStartup failed with error: %d\n", err);
        return 1;
    }

	// Create and verify socket
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket == -1) {
		printf("Socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");

	// Assign IP and port
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(port);

	// Connect the client socket to server socket
	if (connect(client_socket, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("Connection to the server failed...\n");
		exit(0);
	}
	else
		printf("Successfully connected to the server..\n");



     send(client_socket , concat(5,"join channel ", buffer ,", " , p1.token ,"\n"),1000 , 0);
     memset(buffer , 0 , 100);
     recv(client_socket,buffer, 100 ,0 );
        cJSON * buffer_j  =cJSON_Parse( buffer ) ;

printf("%s \n",cJSON_GetObjectItemCaseSensitive (buffer_j , "content") -> valuestring);
         if ( strcasecmp(cJSON_GetObjectItem (buffer_j , "type") -> valuestring , "Error") != 0)
         {
          printf("Request Accepted \n");
          closesocket( server_socket ) ;
          break ;
         }
           else
            printf("Request Rejected \n");
}

    while (true ){
            printf("1_Send message\n") ;
            printf("2_Refresh \n");
            printf("3_Channel members\n") ;
            printf("4_Leave channel\n");
    scanf( "%d" ,&p1.state);
    if (p1.state == 1){
            printf("Enter your massage\n");
       char buffer [100] ;
        scanf("%s" ,&buffer);

             int client_socket, server_socket;
	struct sockaddr_in servaddr, cli;

	WORD wVersionRequested;
    WSADATA wsaData;
    int err;

	// Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h
    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        // Tell the user that we could not find a usable Winsock DLL.
        printf("WSAStartup failed with error: %d\n", err);
        return 1;
    }

	// Create and verify socket
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket == -1) {
		printf("Socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");

	// Assign IP and port
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(port);

	// Connect the client socket to server socket
	if (connect(client_socket, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("Connection to the server failed...\n");
		exit(0);
	}
	else
		printf("Successfully connected to the server..\n");

        send(client_socket,concat(5 ,"send ", buffer , ", ", p1.token, "\n"),100 , 0) ;
        memset(buffer , 0 , 100 ) ;
        recv(client_socket,buffer, 100  ,0 );
        cJSON * buffer_j  =cJSON_Parse( buffer ) ;
         if (strcmp(cJSON_GetObjectItem (buffer_j , "type") -> valuestring , "Error") != 0)
         {
          printf("Request Accepted\n");
          closesocket( server_socket ) ;
          continue;
         }
           else
            {
                printf("Request Rejected\n");
            closesocket( server_socket ) ;
            }
    }
    else if (p1.state == 2) {
   int client_socket, server_socket;
	struct sockaddr_in servaddr, cli;
    char buffer [100000] ;
	WORD wVersionRequested;
    WSADATA wsaData;
    int err;

	// Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h
    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        // Tell the user that we could not find a usable Winsock DLL.
        printf("WSAStartup failed with error: %d\n", err);
        return 1;
    }

	// Create and verify socket
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket == -1) {
		printf("Socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");

	// Assign IP and port
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(port);

	// Connect the client socket to server socket
	if (connect(client_socket, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("Connection to the server failed...\n");
		exit(0);
	}
	else
		printf("Successfully connected to the server..\n");


    send (client_socket , concat(3 , "refresh " ,p1.token, "\n") , 100 ,0);
    memset (buffer , 0 , 100000 ) ;
    recv ( client_socket , buffer , 100000 , 0);
    cJSON * temp =NULL ;
    cJSON * stats =NULL ;
    cJSON * buffer_j  =cJSON_Parse( buffer ) ;

    if (strcmp(cJSON_GetObjectItem( buffer_j , "type") -> valuestring , "Error" ) != 0 )
    {
        printf("Request accepted\n");
    stats = cJSON_GetObjectItemCaseSensitive(buffer_j , "content") ;
    cJSON_ArrayForEach(temp , stats )
    {
        cJSON *sender =cJSON_GetObjectItemCaseSensitive(temp , "sender" ) ;
        cJSON *content =cJSON_GetObjectItemCaseSensitive(temp , "content") ;
        printf("%s : %s \n" , sender -> valuestring , content -> valuestring ) ;
    }
    closesocket(server_socket) ;
    continue ;
    }else
     {printf("Request rejected\n") ;
     closesocket(server_socket) ;
         continue ;
     }
    }




    else if (p1.state == 3){
           int client_socket, server_socket;
	struct sockaddr_in servaddr, cli;
    char buffer [10000] ;
	WORD wVersionRequested;
    WSADATA wsaData;
    int err;

	// Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h
    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        // Tell the user that we could not find a usable Winsock DLL.
        printf("WSAStartup failed with error: %d\n", err);
        return 1;
    }

	// Create and verify socket
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket == -1) {
		printf("Socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");

	// Assign IP and port
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(port);

	// Connect the client socket to server socket
	if (connect(client_socket, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("Connection to the server failed...\n");
		exit(0);
	}
	else
		printf("Successfully connected to the server..\n");

        send(client_socket , concat(3 ,"channel members " , p1.token ,"\n" ) , 100 , 0) ;
        memset(buffer , 0 ,10000);
        recv(client_socket , buffer , 10000 , 0) ;
        cJSON * buffer_j  =cJSON_Parse( buffer ) ;
         if (strcasecmp(cJSON_GetObjectItem (buffer_j , "type") -> valuestring , "Error") != 0 )
         {
          printf("Request Accepted\n");
          printf("members : ") ;
          for (int i = 30 ; i < (strlen( buffer ) - 2) ; i++ )
           {
                 if (buffer [i] == '"')
                printf(" ") ;
                else
               printf ( "%c" , buffer [i]) ;
           }
          printf ("\n" ) ;
          closesocket(server_socket) ;
          continue ;

         }
           else
            printf("Request Rejected\n");
            closesocket( server_socket ) ;



    } else if ( p1.state == 4 ){

               int client_socket, server_socket;
	struct sockaddr_in servaddr, cli;
    char buffer [100] ;
	WORD wVersionRequested;
    WSADATA wsaData;
    int err;

	// Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h
    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        // Tell the user that we could not find a usable Winsock DLL.
        printf("WSAStartup failed with error: %d\n", err);
        return 1;
    }

	// Create and verify socket
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket == -1) {
		printf("Socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");

	// Assign IP and port
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(port);

	// Connect the client socket to server socket
	if (connect(client_socket, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("Connection to the server failed...\n");
		exit(0);
	}
	else
		printf("Successfully connected to the server..\n");

    send (client_socket , concat(3 , "leave " , p1.token , "\n") , 1000, 0 ) ;
    recv(client_socket , buffer , 100 , 0 ) ;
    cJSON * buffer_j  =cJSON_Parse( buffer ) ;

         if (strcmp(cJSON_GetObjectItem (buffer_j , "type") -> valuestring ,"Error") != 0 )
         {
          printf("Request Accepted\n");

          closesocket( server_socket ) ;
            menu (p1) ;
           return ;



         }
           else
            printf("Request Rejected\n");
            closesocket( server_socket ) ;


    }

  }
 menu(p1) ;
}

int main()
{
    struct user p1;
     reglog (p1) ;


}
