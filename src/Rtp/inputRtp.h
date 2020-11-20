#pragma once
/*********************************************
*���ļ���Ŀ���ǽ�socket��onread����inputrtp
*���з���  ��ʹ���Ϊ�����̣߳����͸���
*********************************************/
#ifndef _INPUTRTP_H_
#define _INPUTRTP_H_
#include <iostream>
#include <queue>
#include <Rtp/RtpProcess.h>
#include "Poller/EventPoller.h"
#define QUEUESIZE 2
using namespace std;
using namespace mediakit;


class InputRtp:public std::enable_shared_from_this<InputRtp>
{
public:
	typedef std::shared_ptr<InputRtp> Ptr;

	/* �����ӿ�*/
	static InputRtp& instance();
	~InputRtp();
	bool queuePushSSRC(const Socket::Ptr& sock,const char* data, int data_len, const struct sockaddr* addr, uint32_t* dts_out);
	std::queue<uint32_t > SSRC_Queue;
	void queueInit();//��ʼ������
	static bool Unpack(uint32_t SSRC);//�������
	const char* getData();
	int getDataLen();
private:
    Socket::Ptr sock;
	InputRtp();
    const char* data; 
	int data_len;
    struct sockaddr* addr;
	uint32_t* dts_out;
};

#endif // _INPUTRTP_H_