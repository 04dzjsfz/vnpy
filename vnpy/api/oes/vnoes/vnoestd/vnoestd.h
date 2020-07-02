//ϵͳ
#ifdef WIN32
#include "stdafx.h"
#endif

#include "vnoes.h"
#include "pybind11/pybind11.h"
#include "oes/oes_api/samples/cpp_sample/oes_client_sample.h"


using namespace pybind11;
using namespace Quant360;

//����
#define ONBUSINESSREJECT 0
#define ONORDERINSERT 1
#define ONORDERREPORT 2
#define ONTRADEREPORT 3
#define ONCASHASSETVARIATION 4
#define ONSTOCKHOLDINGVARIATION 5
#define ONOPTIONHOLDINGVARIATION 6
#define ONOPTIONUNDERLYINGHOLDINGVARIATION 7
#define ONSETTLEMENTCONFIRMEDRPT 8
#define ONFUNDTRSFREJECT 9
#define ONFUNDTRSFREPORT 10
#define ONMARKETSTATE 11
#define ONNOTIFYREPORT 12
#define ONREPORTSYNCHRONIZATIONRSP 13
#define ONQUERYORDER 14
#define ONQUERYTRADE 15
#define ONQUERYCASHASSET 16
#define ONQUERYSTKHOLDING 17
#define ONQUERYLOTWINNING 18
#define ONQUERYCUSTINFO 19
#define ONQUERYINVACCT 20
#define ONQUERYCOMMISSIONRATE 21
#define ONQUERYFUNDTRANSFERSERIAL 22
#define ONQUERYISSUE 23
#define ONQUERYSTOCK 24
#define ONQUERYETF 25
#define ONQUERYETFCOMPONENT 26
#define ONQUERYMARKETSTATE 27
#define ONQUERYOPTION 28
#define ONQUERYOPTHOLDING 29
#define ONQUERYOPTUNDERLYINGHOLDING 30
#define ONQUERYOPTPOSITIONLIMIT 31
#define ONQUERYOPTPURCHASELIMIT 32
#define ONQUERYOPTEXERCISEASSIGN 33
#define ONQUERYNOTIFYINFO 34


///-------------------------------------------------------------------------------------
///C++ SPI�Ļص���������ʵ��
///-------------------------------------------------------------------------------------

//API�ļ̳�ʵ��
class TdApi : public OesClientSpi
{
private:
	OesClientApi* api;            //API����
    thread task_thread;                    //�����߳�ָ�루��python���������ݣ�
    TaskQueue task_queue;                //�������
    bool active = false;                //����״̬

public:
    TdApi()
    {
    };

    ~TdApi()
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
	virtual int32       OnConnected(eOesApiChannelTypeT channelType, OesApiSessionInfoT *pSessionInfo, OesApiSubscribeInfoT *pSubscribeInfo = NULL);
	/* ���ӶϿ���Ļص����� */
	virtual int32       OnDisconnected(eOesApiChannelTypeT channelType, OesApiSessionInfoT *pSessionInfo);

	/* ί�оܾ��ر� */
	virtual void        OnBusinessReject(const OesRptMsgHeadT *pRptMsgHead, const OesOrdRejectT *pOrderReject) = 0;
	/* ί�����ջر� */
	virtual void        OnOrderInsert(const OesRptMsgHeadT *pRptMsgHead, const OesOrdCnfmT *pOrderInsert) = 0;
	/* ί��ȷ�ϻر� */
	virtual void        OnOrderReport(const OesRptMsgHeadT *pRptMsgHead, const OesOrdCnfmT *pOrderReport) = 0;
	/* �ɽ�ȷ�ϻر� */
	virtual void        OnTradeReport(const OesRptMsgHeadT *pRptMsgHead, const OesTrdCnfmT *pTradeReport) = 0;
	/* �ʽ�䶯֪ͨ */
	virtual void        OnCashAssetVariation(const OesCashAssetReportT *pCashAssetRpt) = 0;
	/* ��Ʊ�ֱֲ䶯֪ͨ */
	virtual void        OnStockHoldingVariation(const OesStkHoldingReportT *pStkHoldingRpt) = 0;
	/* ��Ȩ�ֱֲ䶯֪ͨ (��������Ȩҵ��) */
	virtual void        OnOptionHoldingVariation(const OesOptHoldingReportT *pOptHoldingRpt) = 0;
	/* ��Ȩ��ĳֱֲ䶯֪ͨ (��������Ȩҵ��) */
	virtual void        OnOptionUnderlyingHoldingVariation(const OesOptUnderlyingHoldingReportT *pUnderlyingHoldingRpt) = 0;
	/* ��Ȩ���㵥ȷ�ϻر� (��������Ȩҵ��) */
	virtual void        OnSettlementConfirmedRpt(const OesRptMsgHeadT *pRptMsgHead, const OesOptSettlementConfirmReportT *pCnfmSettlementRpt) = 0;
	/* �����ί�оܾ��ر� */
	virtual void        OnFundTrsfReject(const OesRptMsgHeadT *pRptMsgHead, const OesFundTrsfRejectT *pFundTrsfReject) = 0;
	/* �����ί��ִ�лر� */
	virtual void        OnFundTrsfReport(const OesRptMsgHeadT *pRptMsgHead, const OesFundTrsfReportT *pFundTrsfReport) = 0;
	/* �г�״̬��Ϣ֪ͨ */
	virtual void        OnMarketState(const OesMarketStateItemT *pMarketStateItem) = 0;
	/* ֪ͨ��Ϣ�ر� */
	virtual void        OnNotifyReport(const OesNotifyInfoReportT *pNotifyInfoRpt) = 0;
	/* �ر�ͬ���������Ӧ */
	virtual void        OnReportSynchronizationRsp(const OesReportSynchronizationRspT *pReportSynchronization) = 0;

	/* ��ѯί����Ϣ�ص� */
	virtual void        OnQueryOrder(const OesOrdItemT *pOrder, const OesQryCursorT *pCursor, int32 requestId) = 0;
	/* ��ѯ�ɽ���Ϣ�ص� */
	virtual void        OnQueryTrade(const OesTrdItemT *pTrade, const OesQryCursorT *pCursor, int32 requestId) = 0;
	/* ��ѯ�ʽ���Ϣ�ص� */
	virtual void        OnQueryCashAsset(const OesCashAssetItemT *pCashAsset, const OesQryCursorT *pCursor, int32 requestId) = 0;
	/* ��ѯ��Ʊ�ֲ���Ϣ�ص� */
	virtual void        OnQueryStkHolding(const OesStkHoldingItemT *pStkHolding, const OesQryCursorT *pCursor, int32 requestId) = 0;
	/* ��ѯ��š���ǩ��Ϣ�ص� */
	virtual void        OnQueryLotWinning(const OesLotWinningItemT *pLotWinning, const OesQryCursorT *pCursor, int32 requestId) = 0;
	/* ��ѯ�ͻ���Ϣ�ص� */
	virtual void        OnQueryCustInfo(const OesCustItemT *pCust, const OesQryCursorT *pCursor, int32 requestId) = 0;
	/* ��ѯ�ɶ��˻���Ϣ�ص� */
	virtual void        OnQueryInvAcct(const OesInvAcctItemT *pInvAcct, const OesQryCursorT *pCursor, int32 requestId) = 0;
	/* ��ѯӶ����Ϣ�ص� */
	virtual void        OnQueryCommissionRate(const OesCommissionRateItemT *pCommissionRate, const OesQryCursorT *pCursor, int32 requestId) = 0;
	/* ��ѯ�������ˮ��Ϣ�ص� */
	virtual void        OnQueryFundTransferSerial(const OesFundTransferSerialItemT *pFundTrsf, const OesQryCursorT *pCursor, int32 requestId) = 0;
	/* ��ѯ֤ȯ������Ϣ�ص� */
	virtual void        OnQueryIssue(const OesIssueItemT *pIssue, const OesQryCursorT *pCursor, int32 requestId) = 0;
	/* ��ѯ֤ȯ��Ϣ�ص� */
	virtual void        OnQueryStock(const OesStockItemT *pStock, const OesQryCursorT *pCursor, int32 requestId) = 0;
	/* ��ѯETF��Ʒ��Ϣ�ص� */
	virtual void        OnQueryEtf(const OesEtfItemT *pEtf, const OesQryCursorT *pCursor, int32 requestId) = 0;
	/* ��ѯETF�ɷֹ���Ϣ�ص� */
	virtual void        OnQueryEtfComponent(const OesEtfComponentItemT *pEtfComponent, const OesQryCursorT *pCursor, int32 requestId) = 0;
	/* ��ѯ�г�״̬��Ϣ�ص� */
	virtual void        OnQueryMarketState(const OesMarketStateItemT *pMarketState, const OesQryCursorT *pCursor, int32 requestId) = 0;
	/* ��ѯ��Ȩ��Ʒ��Ϣ�ص� (��������Ȩҵ��) */
	virtual void        OnQueryOption(const OesOptionItemT *pOption, const OesQryCursorT *pCursor, int32 requestId) = 0;
	/* ��ѯ��Ȩ�ֲ���Ϣ�ص� (��������Ȩҵ��) */
	virtual void        OnQueryOptHolding(const OesOptHoldingItemT *pOptHolding, const OesQryCursorT *pCursor, int32 requestId) = 0;
	/* ��ѯ��Ȩ��ĳֲ���Ϣ�ص� (��������Ȩҵ��) */
	virtual void        OnQueryOptUnderlyingHolding(const OesOptUnderlyingHoldingItemT *pUnderlyingHld, const OesQryCursorT *pCursor, int32 requestId) = 0;
	/* ��ѯ��Ȩ�޲ֶ����Ϣ�ص� (��������Ȩҵ��) */
	virtual void        OnQueryOptPositionLimit(const OesOptPositionLimitItemT *pPositionLimit, const OesQryCursorT *pCursor, int32 requestId) = 0;
	/* ��ѯ��Ȩ�޹������Ϣ�ص� (��������Ȩҵ��) */
	virtual void        OnQueryOptPurchaseLimit(const OesOptPurchaseLimitItemT *pPurchaseLimit, const OesQryCursorT *pCursor, int32 requestId) = 0;
	/* ��ѯ��Ȩ��Ȩָ����Ϣ�ص� (��������Ȩҵ��) */
	virtual void        OnQueryOptExerciseAssign(const OesOptExerciseAssignItemT *pExerciseAssign, const OesQryCursorT *pCursor, int32 requestId) = 0;
	/* ��ѯ֪ͨ��Ϣ�ص� */
	virtual void        OnQueryNotifyInfo(const OesNotifyInfoItemT *pNotifyInfo, const OesQryCursorT *pCursor, int32 requestId) = 0;


    //-------------------------------------------------------------------------------------
    //task������
    //-------------------------------------------------------------------------------------
    void processTask();

	void processBusinessReject(Task *task);

	void processOrderInsert(Task *task);

	void processOrderReport(Task *task);

	void processTradeReport(Task *task);

	void processCashAssetVariation(Task *task);

	void processStockHoldingVariation(Task *task);

	void processOptionHoldingVariation(Task *task);

	void processOptionUnderlyingHoldingVariation(Task *task);

	void processSettlementConfirmedRpt(Task *task);

	void processFundTrsfReject(Task *task);

	void processFundTrsfReport(Task *task);

	void processMarketState(Task *task);

	void processNotifyReport(Task *task);

	void processReportSynchronizationRsp(Task *task);

	void processQueryOrder(Task *task);

	void processQueryTrade(Task *task);

	void processQueryCashAsset(Task *task);

	void processQueryStkHolding(Task *task);

	void processQueryLotWinning(Task *task);

	void processQueryCustInfo(Task *task);

	void processQueryInvAcct(Task *task);

	void processQueryCommissionRate(Task *task);

	void processQueryFundTransferSerial(Task *task);

	void processQueryIssue(Task *task);

	void processQueryStock(Task *task);

	void processQueryEtf(Task *task);

	void processQueryEtfComponent(Task *task);

	void processQueryMarketState(Task *task);

	void processQueryOption(Task *task);

	void processQueryOptHolding(Task *task);

	void processQueryOptUnderlyingHolding(Task *task);

	void processQueryOptPositionLimit(Task *task);

	void processQueryOptPurchaseLimit(Task *task);

	void processQueryOptExerciseAssign(Task *task);

	void processQueryNotifyInfo(Task *task);



    //-------------------------------------------------------------------------------------
    //data���ص������������ֵ�
    //error���ص������Ĵ����ֵ�
    //id������id
    //last���Ƿ�Ϊ��󷵻�
    //i������
    //-------------------------------------------------------------------------------------
    
	virtual void onBusinessReject(const dict &error, const dict &data) {};

	virtual void onOrderInsert(const dict &error, const dict &data) {};

	virtual void onOrderReport(const dict &error, const dict &data) {};

	virtual void onTradeReport(const dict &error, const dict &data) {};

	virtual void onCashAssetVariation(const dict &data) {};

	virtual void onStockHoldingVariation(const dict &data) {};

	virtual void onOptionHoldingVariation(const dict &data) {};

	virtual void onOptionUnderlyingHoldingVariation(const dict &data) {};

	virtual void onSettlementConfirmedRpt(const dict &error, const dict &data) {};

	virtual void onFundTrsfReject(const dict &error, const dict &data) {};

	virtual void onFundTrsfReport(const dict &error, const dict &data) {};

	virtual void onMarketState(const dict &data) {};

	virtual void onNotifyReport(const dict &data) {};

	virtual void onReportSynchronizationRsp(const dict &data) {};

	virtual void onQueryOrder(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryTrade(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryCashAsset(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryStkHolding(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryLotWinning(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryCustInfo(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryInvAcct(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryCommissionRate(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryFundTransferSerial(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryIssue(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryStock(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryEtf(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryEtfComponent(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryMarketState(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryOption(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryOptHolding(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryOptUnderlyingHolding(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryOptPositionLimit(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryOptPurchaseLimit(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryOptExerciseAssign(const dict &data, const dict &error, int reqid) {};

	virtual void onQueryNotifyInfo(const dict &data, const dict &error, int reqid) {};



    //-------------------------------------------------------------------------------------
    //req:���������������ֵ�
    //-------------------------------------------------------------------------------------

    void createFtdcTraderApi(string pszFlowPath = "");

    void release();

    void init();

    int join();

    int exit();

    string getTradingDay();

    void registerFront(string pszFrontAddress);

    void subscribePrivateTopic(int nType);

    void subscribePublicTopic(int nType);



	int queryOrder(const dict &req, int reqid);

	int queryTrade(const dict &req, int reqid);

	int queryCashAsset(const dict &req, int reqid);

	int queryStkHolding(const dict &req, int reqid);

	int queryLotWinning(const dict &req, int reqid);

	int queryCustInfo(const dict &req, int reqid);

	int queryInvAcct(const dict &req, int reqid);

	int queryCommissionRate(const dict &req, int reqid);

	int queryFundTransferSerial(const dict &req, int reqid);

	int queryIssue(const dict &req, int reqid);

	int queryStock(const dict &req, int reqid);

	int queryEtf(const dict &req, int reqid);

	int queryEtfComponent(const dict &req, int reqid);

	int queryMarketState(const dict &req, int reqid);

	int queryCounterCash(const dict &req, int reqid);

	int queryOption(const dict &req, int reqid);

	int queryOptHolding(const dict &req, int reqid);

	int queryOptUnderlyingHolding(const dict &req, int reqid);

	int queryOptPositionLimit(const dict &req, int reqid);

	int queryOptPurchaseLimit(const dict &req, int reqid);

	int queryOptExerciseAssign(const dict &req, int reqid);

	int queryOptSettlementStatement(const dict &req, int reqid);

	int queryNotifyInfo(const dict &req, int reqid);


};
