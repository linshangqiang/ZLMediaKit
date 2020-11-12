
#include "inputRtp.h"

InputRtp& InputRtp::instance()
{
	static InputRtp instance;
	return instance;
}

InputRtp::~InputRtp()
{
}

InputRtp::InputRtp()
{
	//给queue队列初始化两个为0的值
	SSRC_Queue.emplace(0);
	SSRC_Queue.emplace(0);

}
