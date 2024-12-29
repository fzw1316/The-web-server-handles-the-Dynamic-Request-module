#include <ctime>
#include <string>
#include <iostream>

class echoServer {
public:
    void HandleMessage(Connection conn, std::string& message);

private:
    bool isDynamicRequest(const std::string& message);
    std::string generateDynamicContent(const std::string& request);
};
