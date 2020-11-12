#pragma once
/*********************************************
*此文件的目的是将socket的onread与解包inputrtp
*进行分离  ，使其成为两个线程，降低负载
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

	/* 单例接口*/
	static InputRtp& instance();
	~InputRtp();
	void copyData();
private:
	InputRtp();
	std::queue<int > SSRC_Queue;
};

#endif // _INPUTRTP_H_