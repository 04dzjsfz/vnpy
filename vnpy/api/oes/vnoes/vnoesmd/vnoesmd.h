//ϵͳ
#ifdef WIN32
#include "pch.h"
#endif

#include "vnoes.h"
#include "pybind11/pybind11.h"
#include    <mds_api/mds_async_api.h>


using namespace pybind11;
//using namespace Quant360;

//����
#define ONCONNECTED 0
#define ONDISCONNECTED 1
#define ONRTNSTOCKDATA 2
#define ONRTNINDEXDATA 3
#define ONRTNOPTIONDATA 4


///-------------------------------------------------------------------------------------
///C++ SPI�Ļص���������ʵ��
///-------------------------------------------------------------------------------------

	/* API���ǰ������ */
class MdsClientApi;


/**
 * ���׽ӿ���Ӧ��
 */




class MdApi
{
	//int32 defaultClSeqNo = 0;

	//BOOL _isInitialized = FALSE;
	//BOOL _isRunning = FALSE;

	//MdSpi _pSpi = NULL;
	//MdsAsyncApiContextT _pAsyncContext = NULL;
	//MdsAsyncApiChannelT _pDefaultTcpChannel = NULL;
	//// _pQryChannel = NULL;

	//memset(&_apiCfg, 0, sizeof(MdsApiClientCfgT));
	//memset(&_qryChannel, 0, sizeof(MdsApiSessionInfoT));

private:
	MdApi* api;            //API����
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

	virtual void		OnRtnStockData(const MdsMktDataSnapshotHeadT *head, const MdsStockSnapshotBodyT *stock);
	virtual void		OnRtnIndexData(const MdsMktDataSnapshotHeadT *head, const MdsIndexSnapshotBodyT *index);
	virtual void		OnRtnOptionData(const MdsMktDataSnapshotHeadT *head, const MdsStockSnapshotBodyT *option);
	//-------------------------------------------------------------------------------------
	//task������
	//-------------------------------------------------------------------------------------
	void processTask();

	int32 processConnected(Task *task);

	int32 processDisconnected(Task *task);

	void processRtnStockData(Task *task);
	void processRtnIndexData(Task *task);
	void processRtnOptionData(Task *task);

	//-------------------------------------------------------------------------------------
	//data���ص������������ֵ�
	//error���ص������Ĵ����ֵ�
	//id������id
	//last���Ƿ�Ϊ��󷵻�
	//i������
	//-------------------------------------------------------------------------------------


	virtual void onConnected(int channelType, const dict &data) {};

	virtual void onDisconnected(int channelType, const dict &data) {};

	virtual void onRtnStockData(const dict &error, const dict &data) {};
	virtual void onRtnIndexData(const dict &error, const dict &data) {};
	virtual void onRtnOptionData(const dict &error, const dict &data) {};

	//-------------------------------------------------------------------------------------
	//req:���������������ֵ�
	//-------------------------------------------------------------------------------------

	void createMdApi();

	bool loadCfg(string pCfgFile);

	//bool setCustomizedIp(string pIpStr);

	//bool setCustomizedMac(string pMacStr);

	//bool setCustomizedDriverId(string pDriverStr);

	//void setThreadUsername(string pUsername);

	//void setThreadPassword(string pPassword);

	bool init();

	int exit();
	bool subscribeMarketData(const dict &req1, const dict &req2);


	private:
		/* ��ֹ�������캯�� */
		MdApi(const MdApi&);
		/* ��ֹ��ֵ���� */
		MdApi&      operator=(const MdApi&);

	public:
		/* Ϊ�˷���ͻ���ʹ�ö����õ���ˮ�ż�����, ���Ի��ڸ��ֶ�������ά���ͻ���ί����ˮ�� */
		int32               defaultClSeqNo;

	protected:
		MdsApiClientCfgT    _apiCfg;
		MdsApiSessionInfoT  _qryChannel;
		BOOL                _isInitialized;
		BOOL                _isRunning;

		MdSpi        *_pSpi;
		MdsAsyncApiContextT *_pAsyncContext;
		MdsAsyncApiChannelT *_pDefaultTcpChannel;
		MdsApiSessionInfoT  *_pQryChannel;
};


class MdSpi {
//public:
//	/* ���ӻ�����������ɺ�Ļص����� */
//	virtual int32       OnConnected(eMdsApiChannelTypeT channelType, MdsApiSessionInfoT *pSessionInfo, MdsApiSubscribeInfoT *pSubscribeInfo = NULL);
//	/* ���ӶϿ���Ļص����� */
//	virtual int32       OnDisconnected(eMdsApiChannelTypeT channelType, MdsApiSessionInfoT *pSessionInfo);
//
//	virtual void		OnRtnStockData(const MdsMktDataSnapshotHeadT *head, const MdsStockSnapshotBodyT *stock) = 0;
//	virtual void		OnRtnIndexData(const MdsMktDataSnapshotHeadT *head, const MdsIndexSnapshotBodyT *index) = 0;
//	virtual void		OnRtnOptionData(const MdsMktDataSnapshotHeadT *head, const MdsStockSnapshotBodyT *option) = 0;
//



public:
	MdSpi();
	virtual ~MdSpi() {};

public:
	MdApi        *pApi;
	int32               currentRequestId;
};