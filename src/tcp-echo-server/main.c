#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>

typedef struct sockaddr_in sock_addr_in;

void panic(char *msg){
  fprintf(stderr, "Thread panicked with: %s\n", msg);
  exit(1);
}

void *connection_handler(void *descriptor){
  int conn_descriptor = *(int *)descriptor;
  const size_t buffer_size = 10;
  char buffer[buffer_size];
  int n;
  for (;;) {
    memset(&buffer, 0, buffer_size);
    n = read(conn_descriptor, &buffer, buffer_size);
    if (n == 0) {
      printf("Received exit signal\n");
      close(conn_descriptor);
      break;
    }
    else {
      printf("Received bytes from id %d:", conn_descriptor);
      for (int i = 0; i < n; i++){
        printf(" [0x%.8zx]", (size_t)(buffer[i]));
      }
      printf("\n");
      write(conn_descriptor, buffer, n);
    }

  }
  return NULL;
}


int main(void){
  int sock_descriptor, conn_descriptor;
  uint addr_len;
  sock_addr_in server_addr, client_addr;
  char *bind_ip = "127.0.0.1";
  int port = 8080; 
  int max_conn = 2;

  sock_descriptor = socket(AF_INET, SOCK_STREAM, 0); 
  if (sock_descriptor == -1) { panic("Failed to create socket descriptor"); };

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr(bind_ip);
  server_addr.sin_port = htons(port);

  if ((bind(sock_descriptor, (struct sockaddr *) &server_addr, sizeof(server_addr))) != 0){
    panic("Bind failed");
  }

  if ((listen(sock_descriptor, max_conn)) != 0) {
    panic("Fail to listen");
  }
  addr_len = sizeof(client_addr);

  while (
    (conn_descriptor = accept(sock_descriptor, (struct sockaddr *)&client_addr, &addr_len)) > 0
  ){
    pthread_t thread;
    pthread_create(&thread, NULL, connection_handler, &conn_descriptor);
  }
  ;
  if (conn_descriptor < 0){
    panic("Fail to accept");
  }

  close(sock_descriptor);

  return 0;
}
