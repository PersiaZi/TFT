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
    // ����ʵ��
    // ...
}

NetworkManager::NetworkManager()
    : m_socket(INVALID_SOCKET)
    , m_serverIP("100.81.202.165")
    , m_serverPort(8080)
{
    // ��ʼ��Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return;
    }

    // ��ʼ������������Ϣ
    Director::getInstance()->getScheduler()->schedule(
        schedule_selector(NetworkManager::update),
        this,
        0.0f,
        false
    );
}

NetworkManager::~NetworkManager()
{
    // �ر�����
    disconnectFromServer();

    // ����Winsock
    WSACleanup();
}

void NetworkManager::connectToServer(const std::string& serverIP, int serverPort)
{
    // ��������ӵ������������ȶϿ�����
    if (m_socket != INVALID_SOCKET) {
        disconnectFromServer();
    }

    // �����׽���
    m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_socket == INVALID_SOCKET) {
        return;
    }

    // ���÷�������ַ��Ϣ
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(serverIP.c_str());
    serverAddr.sin_port = htons(serverPort);

    // ���ӵ�������
    if (connect(m_socket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        return;
    }


    // ����������Ϣ
    m_serverIP = serverIP;
    m_serverPort = serverPort;
}

void NetworkManager::disconnectFromServer()
{
    if (m_socket != INVALID_SOCKET) {
        // �ر�����
        closesocket(m_socket);
        m_socket = INVALID_SOCKET;

        // ���������Ϣ
        m_serverIP = "";
        m_serverPort = 0;
    }
}

void NetworkManager::sendMessageToServer(const std::string& message)
{
    if (m_socket != INVALID_SOCKET) {
        // ������Ϣ
        send(m_socket, message.c_str(), message.length(), 0);
    }
}

void NetworkManager::addServerMessageListener(cocos2d::Ref* target, cocos2d::SEL_CallFuncO selector)
{
    if (target && selector) {
        // ��Ӽ��������б���
        m_listeners.push_back(target);
    }
}

void NetworkManager::removeServerMessageListener(cocos2d::Ref* target, cocos2d::SEL_CallFuncO selector)
{
    if (target && selector) {
        // ���б����Ƴ�������
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

        // ������Ϣ
        int bytesRead = recv(m_socket, buffer, sizeof(buffer), 0);
        if (bytesRead > 0) {
            std::string message(buffer, bytesRead);

            // ������յ�����Ϣ
            handleReceivedMessage(message);
        }
    }
}

void NetworkManager::handleReceivedMessage(const std::string& message)
{}