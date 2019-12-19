#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

#define SERV_PORT   8000

using namespace cv;
using namespace std;

int main()
{
    /* sock_fd --- socket文件描述符 创建udp套接字*/
    int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock_fd < 0)
    {
        perror("socket");
        exit(1);
    }

    /* 将套接字和IP、端口绑定 */
    struct sockaddr_in addr_serv;
    int len;
    memset(&addr_serv, 0, sizeof(struct sockaddr_in));  //每个字节都用0填充
    addr_serv.sin_family = AF_INET;    //使用IPV4地址
    addr_serv.sin_port = htons(SERV_PORT);   //端口
    /* INADDR_ANY表示不管是哪个网卡接收到数据，只要目的端口是SERV_PORT，就会被该应用程序接收到 */
    addr_serv.sin_addr.s_addr = htonl(INADDR_ANY);  //自动获取IP地址
    len = sizeof(addr_serv);

    /* 绑定socket */
    if(bind(sock_fd, (struct sockaddr *)&addr_serv, sizeof(addr_serv)) < 0)
    {
        perror("bind error:");
        exit(1);
    }

    int recv_num;
    struct sockaddr_in addr_client;
    int width = 1280;
    int height = 800;
    void* buf = malloc(width+4);  // 加四个字节代表行数
    while(1)
    {
        Mat gray = Mat(Size(width,height), CV_8UC1);
        int receiveByte = width+4; // 接收总字节数，灰度图
        int rowIndex = 0;
        do
        {
            recv_num = recvfrom(sock_fd, buf, receiveByte, 0, (struct sockaddr *)&addr_client, (socklen_t *)&len);
            rowIndex = ((uint*)buf)[0];
            memcpy(gray.ptr(rowIndex), buf+4, width);
            if(recv_num < 0)
            {
                perror("recvfrom error:");
                exit(1);
            }
        }
        while (rowIndex < height-1);

        cout << "receive gray image." << endl;
        // 把接收到的灰度图显示出来
        imshow("receive image", gray);
        waitKey(10);
    }

    free(buf);
    close(sock_fd);

    return 0;
}