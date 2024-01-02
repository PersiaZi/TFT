#include "cocos2d.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include"network.h"
#pragma comment(lib, "ws2_32.lib")
USING_NS_CC;


NetworkManager* NetworkManager::getInstance()
{
    static NetworkManager instance;
    return &instance;
}

void NetworkManager::destroyInstance()
{
    // 清理实例
    // ...
}

NetworkManager::NetworkManager()
    : m_socket(INVALID_SOCKET)
    , m_serverIP("100.81.202.165")
    , m_serverPort(8080)
{
    // 初始化Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return;
    }

    // 开始监听服务器消息
    Director::getInstance()->getScheduler()->schedule(
        schedule_selector(NetworkManager::update),
        this,
        0.0f,
        false
    );
}

NetworkManager::~NetworkManager()
{
    // 关闭连接
    disconnectFromServer();

    // 清理Winsock
    WSACleanup();
}

void NetworkManager::connectToServer(const std::string& serverIP, int serverPort)
{
    // 如果已连接到服务器，则先断开连接
    if (m_socket != INVALID_SOCKET) {
        disconnectFromServer();
    }

    // 创建套接字
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket == INVALID_SOCKET) {
        return;
    }

    // 设置服务器地址信息
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(serverIP.c_str());
    serverAddr.sin_port = htons(serverPort);

    // 连接到服务器
    if (connect(m_socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        return;
    }


    // 更新连接信息
    m_serverIP = serverIP;
    m_serverPort = serverPort;
}

void NetworkManager::disconnectFromServer()
{
    if (m_socket != INVALID_SOCKET) {
        // 关闭连接
        closesocket(m_socket);
        m_socket = INVALID_SOCKET;

        // 清空连接信息
        m_serverIP = "";
        m_serverPort = 0;
    }
}

void NetworkManager::sendMessageToServer(const std::string& message)
{
    if (m_socket != INVALID_SOCKET) {
        // 发送消息
        send(m_socket, message.c_str(), message.length(), 0);
    }
}

void NetworkManager::addServerMessageListener(cocos2d::Ref* target, cocos2d::SEL_CallFuncO selector)
{
    if (target && selector) {
        // 添加监听器到列表中
        m_listeners.push_back(target);
    }
}

void NetworkManager::removeServerMessageListener(cocos2d::Ref* target, cocos2d::SEL_CallFuncO selector)
{
    if (target && selector) {
        // 从列表中移除监听器
        for (auto it = m_listeners.begin(); it != m_listeners.end(); ++it) {
            if (*it == target) {
                m_listeners.erase(it);
                break;
            }
        }
    }
}

void NetworkManager::update(float dt)
{
    if (m_socket != INVALID_SOCKET) {
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));

        // 接收消息
        int bytesRead = recv(m_socket, buffer, sizeof(buffer), 0);
        if (bytesRead > 0) {
            std::string message(buffer, bytesRead);

            // 处理接收到的消息
            handleReceivedMessage(message);
        }
    }
}

void NetworkManager::handleReceivedMessage(const std::string& message)
{}