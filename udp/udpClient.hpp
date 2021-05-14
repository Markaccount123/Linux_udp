#include<iostream>
#include<string>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
class udpClient{
  private:
    std::string ip;
    int port;//对于端口号当然也可以定义为short类型，2字节
    int sock;
  public:
    //因为客户端需要链接服务器，所以这里应该需要的是Server端的ip和port
    udpClient(std::string _ip = "127.0.0.1",int _port = 8080)
      :ip(_ip),port(_port)
    {}

    void initClient()
    {
      //第一步应该先创建套接字
      sock = socket(AF_INET,SOCK_DGRAM,0);//第一个参数-协议家族中的哪一个协议 第二个参数①面向字节流TCP ②用户数据报 UDP 第三个参数设置为0，使用默认的行为

      //客户端是不需要绑定的
    }

    void start()
    {
      std::string msg;
      struct sockaddr_in peer; //表示服务器
      peer.sin_family = AF_INET;
      peer.sin_port = htons(port);
      peer.sin_addr.s_addr = inet_addr(ip.c_str());
      for(;;){
        std::cout<< "Please Enter# ";
        std::cin>>msg;


        //对于Client来说，应该是要先给Server端发送数据，然后在接收
        sendto(sock,msg.c_str(),msg.size(),0,(struct sockaddr*)&peer,sizeof(peer));

        char echo[128];
        ssize_t s = recvfrom(sock,echo,sizeof(echo)-1,0,nullptr,nullptr);
        if(s > 0){
          echo[s] = 0;
          std::cout<<"Server# "<<echo<<std::endl;
        }
      }
    }
    ~udpClient()
    {
      close(sock);
    }
};
