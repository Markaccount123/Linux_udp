#include<iostream>
#include<string>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
class udpServer{
  private:
    std::string ip;
    int port;//对于端口号当然也可以定义为short类型，2字节
    int sock;
  public:
    udpServer(std::string _ip = "127.0.0.1",int _port = 8080)
      :ip(_ip),port(_port)
    {}

    void initServer()
    {
      //第一步应该先创建套接字
      sock = socket(AF_INET,SOCK_DGRAM,0);//第一个参数-协议家族中的哪一个协议 第二个参数①面向字节流TCP ②用户数据报 UDP 第三个参数设置为0，使用默认的行为

      struct sockaddr_in local;//这个是一个临时变量，在用户栈上所定义出来变量，要想把它写入到操作系统中，还需要一步
      local.sin_family = AF_INET;
      local.sin_port = htons(port);
      local.sin_addr.s_addr = inet_addr(ip.c_str()); //ip是一个STL的容器，所以要把它转换为c语言形式

      if(bind(sock,(struct sockaddr*)&local,sizeof(local)) < 0){
        std::cerr<< "bind error"<<std::endl;
        exit(1); //终止进程
      }
    }

    void start()
    {
      char msg[64]; //接收的缓冲区
      //对于服务器来说，我不希望他终止，我要她一直运行下去，所以需要一个死循环
      for(;;){
        msg[0] = '\0';
        //ssize_t 是一个int类型，是一个有符号的
        struct sockaddr_in end_point; //表示对端
        socklen_t len = sizeof(end_point);
        ssize_t s = recvfrom(sock,msg,sizeof(msg)-1,0,(struct sockaddr*)&end_point,&len);
        if(s > 0){
          msg[s] = '\0';
          std::cout<< "Client# "<< msg <<std::endl;

          //我希望接收以后在Server端打印出来，返回都去的数值再加上一定的标识，说明Server接收到了的应答
          std::string echo_string = msg;
          echo_string += " [Server echo!] ";
          sendto(sock,echo_string.c_str(),echo_string.size(),0,(struct sockaddr*)&end_point,len);
        }
      }
    }
    ~udpServer()
    {
      close(sock);
    }
};
