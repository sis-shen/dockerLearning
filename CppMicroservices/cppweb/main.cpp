#include <iostream> 
#include <netinet/in.h> //sockaddr_in结构体头文件 
#include <string.h> //memset()头文件 
#include <assert.h> //assert()头文件 
#include <unistd.h> //close()头文件 
#include <pthread.h> 
 
 
struct pthread_data{ 
    struct sockaddr_in client_addr; 
    int sock_fd; 
}; 
 
using namespace  std; 
 
void *serverForClient(void *arg); 
 
int main(){ 
    int socket_fd; 
    int conn_fd; 
    int res; 
    int len; 
 
    struct sockaddr_in sever_add; 
    memset(&sever_add,0,sizeof(sever_add)); //初始化 
    sever_add.sin_family = PF_INET; 
    sever_add.sin_addr.s_addr = htons(INADDR_ANY); 
    sever_add.sin_port = htons(8081); 
    len = sizeof(sever_add); 
 
    //socket() 
    int option = 1; 
    socket_fd =  socket(AF_INET,SOCK_STREAM,0); 
    assert(socket_fd >= 0); 
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option)); 
 
    //bind() 
    res = bind(socket_fd,(struct sockaddr*)&sever_add,len); 
    perror("bind"); 
    assert(res != -1); 
 
    //listen() 
    res = listen(socket_fd,1); 
    assert(res != -1); 
    cout<<"server init"<<endl; 
 
    while(1){ 
        struct sockaddr_in client; 
        int client_len = sizeof(client); 
        //accept() 
        conn_fd = accept(socket_fd,(struct sockaddr*)&client,(socklen_t *)&client_len); 
 
        pthread_data pdata; 
        pthread_t pt; 
        pdata.client_addr = client; 
        pdata.sock_fd = conn_fd; 
        std::cout<<"in "<<conn_fd<<endl; 
        pthread_create(&pt, NULL, serverForClient, (void *)&pdata); 
    } 
 
    return 0; 
} 
 
 
void *serverForClient(void *arg){ 
    struct pthread_data *pdata = (struct pthread_data*)arg;
    int conn_fd = pdata->sock_fd; 
 
    std::cout<<"process "<<conn_fd<<endl; 
 
    if(conn_fd < 0) cout << "error" << endl; 
    else{ 
        char request[1024]; 
        int len = recv(conn_fd,request,1024,0); 
 
        if(len <= 0){ 
            close(conn_fd); 
            return nullptr; 
        } 
 
        request[strlen(request) + 1] = '\0'; 
        char buf[520] = "HTTP/1.1 200 ok\r\nconnection: close\r\n\r\n";//HTTP响应 
        int s = send(conn_fd,buf,strlen(buf),0);//发送响应 
        if(s <=0 ){ 
            perror("send"); 
            return nullptr; 
        } else{ 
            char buf2[1024] = "\n" 
                              "<!DOCTYPE html>\n" 
                              "<html>\n" 
                              "<head>\n" 
                              "<title>Welcome to C++ web server!</title>\n" 
                              "<style>\n" 
                              "html { color-scheme: light dark; }\n" 
                              "body { width: 35em; margin: 0 auto;\n" 
                              "font-family: Tahoma, Verdana, Arial, sans-serif; }\n" 
                              "</style>\n" 
                              "</head>\n" 
                              "<body>\n" 
                              "<h1>Welcome to C++ webserver!</h1>\n" 
                              "<p>If you see this page, the nginx web server is successfully installed and\n" 
                              "working. Further configuration is required.</p>\n" 
                              "\n" 
                              "<p><em>Thank you for using webserver.</em></p>\n" 
                              "</body>\n" 
                              "</html>"; 
            int s2 = send(conn_fd,buf2,strlen(buf2),0); 
            if(s2<=0){ 
                perror("send"); 
                return nullptr; 
            } 
            //发送响应 
            close(conn_fd); 
        } 
 
    } 
    return nullptr; 
}