/*************************************************************************
	> File Name: 1.client.c
	> Author: 
	> Mail: 
	> Created Time: Fri 23 Oct 2020 07:53:44 PM CST
 ************************************************************************/

#include<stdio.h>

int server_port = 0;
char server_ip[20] = {0};
int team = -1;
char *conf = "./football.conf";
int sockfd = -1;

int main(int argc, char **argv) {
   int opt;
   struct LogRequest request;
   struct LogResponse response;

   bzero(&request, sizeof(request));
   bzero(&response, sizeof(response));

   while ((opt = getopt(argc, argv, "h:p:t:m:n:")) != -1) {

  }

   struct sockaddr_in server;
   server.sin_family = AF_INET;
   server.sin_port = htons(server_port);
   server.sin_addr.s_addr = inet_addr(server_ip);

   socklen_t len = sizeof(server);

   if ((sockfd = socket_udp()) < 0) {
       perror("socket_udp()");
       exit(1);
  }
   sendto(sockfd, (void *)&request, sizeof(request), 0, (struct sockaddr *)&server, len);



   // 在这里，请使用select做定时，如果超过时间没有收到数据，判定为server不在线

   // retval就是select的返回值

   if (retval < 0) {
       perror("select");
       exit(1);
  } else if (retval){
       int ret = recvfrom(sockfd, (void *)&response, sizeof(response), 0, (struct sockaddr *)&server, &len);
       if (ret != sizeof(response) || response.type) {
           printf("The Game Server refused your login.\n\tThis May be helpful:%s\n", response.msg);
           exit(1);
      }
  } else {
       printf("The Game Server is out of service!.\n");
       exit(1);
  }

   printf("Server : %s\n", response.msg);
   connect(sockfd, (struct sockaddr *)&server, len)；

   //是否需要更多的逻辑或者数据传输来测试，请自己决定，如果需要，在服务端，应该用多线程


   return 0;
}
