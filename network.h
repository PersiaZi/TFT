#pragma once
#include "cocos2d.h"
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")
USING_NS_CC;

class NetworkManager : public cocos2d::Ref
{
public:
    static NetworkManager* getInstance();
    void destroyInstance();

    void connectToServer(const std::string& serverIP, int serverPort);
    void disconnectFromServer();
    void sendMessageToServer(const std::string& message);

    // ��ӷ�������Ϣ������
    void addServerMessageListener(cocos2d::Ref* target, cocos2d::SEL_CallFuncO selector);
    // �Ƴ���������Ϣ������
    void removeServerMessageListener(cocos2d::Ref* target, cocos2d::SEL_CallFuncO selector);


    NetworkManager();
    ~NetworkManager();

    void update(float dt);
    void handleReceivedMessage(const std::string& message);
private:
    SOCKET m_socket;
    std::string m_serverIP;
    int m_serverPort;
    std::vector<cocos2d::Ref*> m_listeners;
};