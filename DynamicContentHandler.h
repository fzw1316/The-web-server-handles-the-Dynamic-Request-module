#pragma once
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <memory>
#include <ctime>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

class Connection {
public:
    void send(const std::string& data, size_t length);
};

class echoServer {
public:
    bool isDynamicRequest(const std::string& message);
    std::string generateDynamicContent(const std::string& request);
    void HandleMessage(std::shared_ptr<Connection> conn, std::string& message);

private:
    std::string handleCGIRequest(const std::string& scriptPath, const std::string& queryString);
};
