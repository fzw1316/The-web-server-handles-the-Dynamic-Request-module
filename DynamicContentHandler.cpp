#include "DynamicContentHandler.h"

// 判断是否是动态请求
bool echoServer::isDynamicRequest(const std::string& message) {
    return message.find("/api/") != std::string::npos || message.find(".cgi") != std::string::npos;
}

// 生成动态内容
std::string echoServer::generateDynamicContent(const std::string& request) {
    if (request.find("GET /api/time") == 0) {
        // 返回当前时间
        time_t now = time(0);
        struct tm tstruct;
        char buf[80];
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

        return "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nCurrent time: " + std::string(buf);
    }

    if (request.find("GET /api/echo?") == 0) {
        // 简单实现查询字符串回显
        size_t queryStart = request.find('?') + 1;
        std::string query = request.substr(queryStart);
        std::map<std::string, std::string> params;

        // 解析查询字符串
        std::istringstream queryStream(query);
        std::string keyValue;
        while (std::getline(queryStream, keyValue, '&')) {
            size_t equalsPos = keyValue.find('=');
            if (equalsPos != std::string::npos) {
                std::string key = keyValue.substr(0, equalsPos);
                std::string value = keyValue.substr(equalsPos + 1);
                params[key] = value;
            }
        }

        // 返回解析的参数
        std::ostringstream response;
        response << "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n";
        response << "Echoed parameters:\n";
        for (const auto& [key, value] : params) {
            response << key << ": " << value << "\n";
        }

        return response.str();
    }

    // 未知请求返回404
    return "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nPage not found.";
}

// 处理消息的主函数
void echoServer::HandleMessage(std::shared_ptr<Connection> conn, std::string& message) {
    if (isDynamicRequest(message)) {
        // 如果是动态请求，生成动态内容并发送
        std::string response = generateDynamicContent(message);
        conn->send(response, response.size());
    } else {
        // 处理其他请求
        std::string response = "HTTP/1.1 400 Bad Request\r\nContent-Type: text/plain\r\n\r\nBad Request.";
        conn->send(response, response.size());
    }
}

// 模拟的Connection类实现
void Connection::send(const std::string& data, size_t length) {
    // 简单输出模拟发送
    std::cout << "Sending Response (" << length << " bytes):\n" << data << std::endl;
}

