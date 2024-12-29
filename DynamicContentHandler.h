#ifndef ECHOSERVER_H
#define ECHOSERVER_H

#include <string>
#include <ctime>
#include <memory>
#include <sstream>
#include <iostream>
#include <map>

// 模拟的Connection类
class Connection {
public:
    void send(const std::string& data, size_t length);
};

class echoServer {
public:
    // 检查请求是否为动态请求
    static bool isDynamicRequest(const std::string& message);

    // 处理动态内容请求
    static std::string generateDynamicContent(const std::string& request);

    // 处理消息的主函数
    void HandleMessage(std::shared_ptr<Connection> conn, std::string& message);
};

#endif // ECHOSERVER_H
