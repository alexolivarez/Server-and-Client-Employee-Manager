/* server.c - code for example server program that uses TCP */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

struct employee_info {
  char ID[7]; 
  char name[10]; 
  double salary;
};

main(argc, argv)
     int     argc;
     char    *argv[];
{
  struct  sockaddr_in sad; /* structure to hold server's address  */
  int     port;            /* protocol port number                */
  
  struct  sockaddr_in cad; /* structure to hold client's address  */
  int     alen;            /* length of address                   */
  
  int     welcomeSocket, connectionSocket; /* socket descriptors  */
  
  struct  employee_info DB[10] = { {"abc123","Turgay", 100000.0}, {"ejl483","Alex O", 25000.0}, {"gyr286","Maggie D", 100000000.0}, {"asd234","Gina F", 1000000.0}, {"lje384","harsh", 26500.0}, {"zxc442","yakob", 255000.0}, {"vds233","lone", 205000.0}, {"hrd455","berto", 225000.0}, {"bbb332","bird", 245000.0}, {"efh563","serge", 220000.0},};
	char    clientSentence[128]; 
  char    inputID[128];
  char    reply[128];
  //strcpy(reply, "Hello ");
  char    salaryWord[128];
  char    name[128];
  char    reply2[128];
  char    buff[128];
  int     i, n;
  
  /* Check command-line argument for protocol port and extract   */
  /* port number if one is specified. Otherwise, give error      */
  if (argc > 1) {                /* if argument specified        */
    port = atoi(argv[1]);        /* convert argument to binary   */
  } else { 
    fprintf(stderr,"Usage: %s port-number\n",argv[0]);
    exit(1);
  }
  
  /* Create a socket */

  welcomeSocket = socket(PF_INET, SOCK_STREAM, 0); /* CREATE SOCKET */
  if (welcomeSocket < 0) {
    fprintf(stderr, "socket creation failed\n");
    exit(1);
  }
  
  /* Bind a local address to the socket */
  
  memset((char *)&sad,0,sizeof(sad)); /* clear sockaddr structure   */
  sad.sin_family = AF_INET;           /* set family to Internet     */
  sad.sin_addr.s_addr = INADDR_ANY;   /* set the local IP address   */
  sad.sin_port = htons((u_short)port);/* set the port number        */ 
  
  if (bind(welcomeSocket, (struct sockaddr *)&sad, sizeof(sad)) < 0) {
    fprintf(stderr,"bind failed\n");
    exit(1);
  }
  
  /* Specify the size of request queue */
  
  if (listen(welcomeSocket, 10) < 0) {
    fprintf(stderr,"listen failed\n");
    exit(1);
  }
  
  /* Main server loop - accept and handle requests */
  
  while (1) {
    alen = sizeof(cad);
    if ( (connectionSocket=accept(welcomeSocket, (struct sockaddr *)&cad, &alen)) < 0) {
      fprintf(stderr, "accept failed\n");
      exit(1);
    }
    
    /* Get the sentence from the client */
    
    clientSentence[0]='\0';
    reply[0]='\0';
    salaryWord[0]='\0';
    salaryWord[1]=' ';
    name[0]='\0';
    reply2[0]='\0';
    n=read(connectionSocket,buff,sizeof(buff));
    while(n > 0){
      strncat(clientSentence,buff,n);
      if (buff[n-1]=='\0') break;
      n=read(connectionSocket,buff,sizeof(buff));
    }
    int res = 0;
    /* Capitalize the sentence */
    // instead, check if id exists in DB
    for(i=0; i < 10; i++){
        if(strcmp(DB[i].ID, clientSentence) == 0){
          strcpy(inputID, clientSentence);
          strcpy(name, DB[i].name);
          strcat(reply, name);
          strcat(reply, "! Salary: ");
          snprintf(salaryWord, 50, "%f", DB[i].salary);
          strcat(reply, salaryWord);
        }
        else{
          //res +=strcmp(DB[i].ID, clientSentence);
          //if(res != 0){strcat(reply, ", ID not found");}
        }
    }
    
    /* send it to the client */
    
    write(connectionSocket, reply, strlen(reply)+1);
    close(connectionSocket);
  }
}





