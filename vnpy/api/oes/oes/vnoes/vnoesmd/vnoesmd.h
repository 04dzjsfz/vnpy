//ϵͳ
#ifdef WIN32
#include "pch.h"
#endif

#include "vnoes.h"
#include "pybind11/pybind11.h"
#include "mds_client_sample.h"

using namespace pybind11;
using namespace Quant360;

//����
#define ONCONNECTED 0
#define ONDISCONNECTED 1


///-------------------------------------------------------------------------------------
///C++ SPI�Ļص���������ʵ��
///-------------------------------------------------------------------------------------

//API�ļ̳�ʵ��
class MdApi : public MdsClientSpi
{
private:
	MdsClientApi* api;            //API����
	thread task_thread;                    //�����߳�ָ�루��python���������ݣ�
	TaskQueue task_queue;                //�������
	bool active = false;                //����״̬

public:
	MdApi()
	{
	};

	~MdApi()
	{
		if (this->active)
		{
			this->exit();
		}
	};

	//-------------------------------------------------------------------------------------
	//API�ص�����
	//-------------------------------------------------------------------------------------



		/* ���ӻ�����������ɺ�Ļص����� */
	virtual int32       OnConnected(eMdsApiChannelTypeT channelType, MdsApiSessionInfoT *pSessionInfo, MdsApiSubscribeInfoT *pSubscribeInfo = NULL);
	/* ���ӶϿ���Ļص����� */
	virtual int32       OnDisconnected(eMdsApiChannelTypeT channelType, MdsApiSessionInfoT *pSessionInfo);

	//-------------------------------------------------------------------------------------
	//task������
	//-------------------------------------------------------------------------------------
	void processTask();

	int32 processConnected(Task *task);

	int32 processDisconnected(Task *task);

	//-------------------------------------------------------------------------------------
	//data���ص������������ֵ�
	//error���ص������Ĵ����ֵ�
	//id������id
	//last���Ƿ�Ϊ��󷵻�
	//i������
	//-------------------------------------------------------------------------------------


	virtual void onConnected(int channelType, const dict &data) {};

	virtual void onDisconnected(int channelType, const dict &data) {};

	//-------------------------------------------------------------------------------------
	//req:���������������ֵ�
	//-------------------------------------------------------------------------------------

	void createMdApi();

	bool loadCfg(string pCfgFile);

	bool setCustomizedIp(string pIpStr);

	bool setCustomizedMac(string pMacStr);

	bool setCustomizedDriverId(string pDriverStr);

	void setThreadUsername(string pUsername);

	void setThreadPassword(string pPassword);

	bool init();

	int exit();

};