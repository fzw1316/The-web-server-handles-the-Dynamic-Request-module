#include"DynamicContentHandler.h"
bool echoServer::isDynamicRequest(const std::string& message) {
    // 判断是否是动态请求
    return message.find("/api/") == 0 || message.find(".cgi") != std::string::npos;
}

std::string echoServer::generateDynamicContent(const std::string& request) {
    if (request.find("/api/time") == 0) {
        // 返回当前时间
        time_t now = time(0);
        struct tm tstruct;
        char buf[80];
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);
        return "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nCurrent time: " + std::string(buf);
    }

    if (request.find("/api/greeting") == 0) {
        // 返回一个模拟的问候消息
        return "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello, world!";
    }

    // 默认返回错误
    return "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nPage not found.";
}

void echoServer::HandleMessage(Connection conn, std::string& message) {
    if (isDynamicRequest(message)) {
        // 如果是动态请求，生成动态内容并发送
        std::string response = generateDynamicContent(message);
        conn->send(response, response.size());
    }
}
