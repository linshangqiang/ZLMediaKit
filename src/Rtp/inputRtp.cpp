
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
	//��queue���г�ʼ������Ϊ0��ֵ
	SSRC_Queue.emplace(0);
	SSRC_Queue.emplace(0);

}
