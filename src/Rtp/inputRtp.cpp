
#include "inputRtp.h"
#include "Rtp/RtpSelector.h"
#include "Rtp/RtpProcess.cpp"
#include "string.h"


InputRtp& InputRtp::instance()
{
	static InputRtp instance;
	return instance;
}

InputRtp::~InputRtp()
{
}

bool InputRtp::queuePushSSRC(const Socket::Ptr& sock, const char* data, int data_len, const struct sockaddr* addr, uint32_t* dts_out)
{

	this->data = data;
	this->data_len = data_len;
	this->sock =sock;
	memcpy(this->addr, addr, sizeof(struct sockaddr));
	this->dts_out = dts_out;
	//cout<<"address dismatch111111:" << printAddress(InputRtp::instance().addr) << endl;
	uint32_t ssrc = 0;
	if (!RtpSelector::Instance().getSSRC(data, data_len, ssrc)) {
		WarnL << "get ssrc from rtp failed:" << data_len;
		return false;
	}
	SSRC_Queue.emplace(ssrc);
	PipeWrap _pipe;
	SockUtil::setNoBlocked(_pipe.readFD());
	EventPoller::Instance().packetEvent(_pipe.readFD(), ssrc, InputRtp::instance().Unpack);
	return true;
}

void InputRtp::queueInit()
{
	for (unsigned int i = 0; i < QUEUESIZE; i++)
	{
		SSRC_Queue.emplace(0);
	}
}

bool InputRtp::Unpack(uint32_t SSRC)
{
	//cout << "address dismatch2222222:" << printAddress(InputRtp::instance().addr) << endl;
	//InputRtp::instance().SSRC_Queue.push(11);
//	InputRtp::instance().SSRC_Queue.pop();
	InputRtp::instance().SSRC_Queue.front() = SSRC;
	auto process = RtpSelector::Instance().getProcess(printSSRC(SSRC), true);
	if (process) {
		try {
			return process->inputRtp(true, InputRtp::instance().sock, InputRtp::instance().data, InputRtp::instance().data_len, InputRtp::instance().addr, InputRtp::instance().dts_out);
		}
		catch (...) {
			RtpSelector::Instance().delProcess(printSSRC(SSRC), process.get());
			throw;
		}
	}
	InputRtp::instance().SSRC_Queue.pop();
	//cout<< InputRtp::instance().SSRC_Queue.front()<<endl;
	
	cout << "正在解包" << InputRtp::instance().SSRC_Queue.front()<<endl;
}



const char* InputRtp::getData()
{
	return this->data;
}

int InputRtp::getDataLen()
{
	return this->data_len;
}

InputRtp::InputRtp()
{
	this->sock = nullptr;
	this->data = 0;
	this->data_len = 0;
	this->addr = (struct sockaddr*)malloc(sizeof(struct sockaddr));
	//this->addr = nullptr;
	//this->dts_out = nullptr;
}
