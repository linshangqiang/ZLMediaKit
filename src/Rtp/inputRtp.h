#pragma once
/*********************************************
*���ļ���Ŀ���ǽ�socket��onread����inputrtp
*���з���  ��ʹ���Ϊ�����̣߳����͸���
*********************************************/
#ifndef _INPUTRTP_H_
#define _INPUTRTP_H_
#include <iostream>
#include <queue>
using namespace std;

class InputRtp:public std::enable_shared_from_this<InputRtp>
{
public:
	typedef std::shared_ptr<InputRtp> Ptr;

	/* �����ӿ�*/
	static InputRtp& instance();
	~InputRtp();
	void copyData();
private:
	InputRtp();
	std::queue<int > SSRC_Queue;
};

#endif // _INPUTRTP_H_