#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <opencv2/opencv.hpp>

#define DEST_PORT 8000
#define DSET_IP_ADDRESS  "127.0.0.1"

using namespace cv;

int main()
{
    /* socket文件描述符 */
    int sock_fd;

    /* 建立udp socket */
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock_fd < 0)
    {
        perror("socket");
        exit(1);
    }

    /* 设置address */
    struct sockaddr_in addr_serv;
    int len;
    memset(&addr_serv, 0, sizeof(addr_serv));
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_addr.s_addr = inet_addr(DSET_IP_ADDRESS);
    addr_serv.sin_port = htons(DEST_PORT);
    len = sizeof(addr_serv);

    Mat gray = imread("./testImg/test.png", IMREAD_ANYDEPTH | IMREAD_ANYCOLOR);
    int width = gray.cols;
    int height = gray.rows;
    void* buf = malloc(width+4);  // 加四个字节代表行数
    while(1)
    {
        int sendBytes = width*height;
        int send_num = width+4;
        int res = -1;

        printf("client send one gray image.\n");

        // 每次发一行
        for(int j=0; j < height; ++j)
        {
            auto row = gray.ptr(j);
            ((uint*)buf)[0] = j;
            memcpy(buf+4, row, width);
            res = sendto(sock_fd, buf, send_num, 0, (struct sockaddr *)&addr_serv, len);
        }

        if(res < 0)
        {
            perror("sendto error:");
            exit(1);
        }

        usleep(100*1000); // 100ms
    }

    free(buf);
    close(sock_fd);

    return 0;
}