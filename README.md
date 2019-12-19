# udpsocks-demo
Linux C/C++ UDP Socket通信实例
### 例子说明
该例子实现client发送一张灰度图接着server接收这张灰度图，由于socks不能直接整张图发送，因为图片过大，所以改成一行行发并在前面空出４字节保存图像的行数。

### 参考
https://www.cnblogs.com/zkfopen/p/9382705.html
