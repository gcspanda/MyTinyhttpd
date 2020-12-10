#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
 int sockfd;
 int len;
 struct sockaddr_in address;
 int result;
 char buf[] = "GET / HTTP/1.1\n\n\n";
 char get[1024] = {0};
 sockfd = socket(AF_INET, SOCK_STREAM, 0);
 address.sin_family = AF_INET;
 address.sin_addr.s_addr = inet_addr("127.0.0.1");/*本机IP地址*/
 address.sin_port = htons(4400);/*tinyhttpd的端口*/
 len = sizeof(address);
 result = connect(sockfd, (struct sockaddr *)&address, len);
 if (result == -1)
 {
  perror("oops:client:");
  _exit(1);
 }
 write(sockfd,buf, sizeof(buf));/*发送请求*/
 read(sockfd,get, sizeof(get));/*接收返回数据*/
 /*打印返回数据*/
 printf("-----------------------------show buffer -----------------------------\n");
 printf("%s",get);
 printf("----------------------------------------------------------------------\n");
 close(sockfd);
 _exit(0);
}
