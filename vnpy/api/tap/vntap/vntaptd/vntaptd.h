//ϵͳ
#ifdef WIN32
#include "stdafx.h"
#endif

#include "vntap.h"
#include "pybind11/pybind11.h"
#include "tap/iTapTradeAPI.h"


using namespace pybind11;
using namespace ITapTrade;

//����
#define ONCONNECT 0
#define ONRSPLOGIN 1
#define ONRTNCONTACTINFO 2
#define ONRSPREQUESTVERTIFICATECODE 3
#define ONEXPRIATIONDATE 4
#define ONAPIREADY 5
#define ONDISCONNECT 6
#define ONRSPCHANGEPASSWORD 7
#define ONRSPAUTHPASSWORD 8
#define ONRSPQRYTRADINGDATE 9
#define ONRSPSETRESERVEDINFO 10
#define ONRSPQRYACCOUNT 11
#define ONRSPQRYFUND 12
#define ONRTNFUND 13
#define ONRSPQRYEXCHANGE 14
#define ONRSPQRYCOMMODITY 15
#define ONRSPQRYCONTRACT 16
#define ONRTNCONTRACT 17
#define ONRSPORDERACTION 18
#define ONRTNORDER 19
#define ONRSPQRYORDER 20
#define ONRSPQRYORDERPROCESS 21
#define ONRSPQRYFILL 22
#define ONRTNFILL 23
#define ONRSPQRYPOSITION 24
#define ONRTNPOSITION 25
#define ONRSPQRYPOSITIONSUMMARY 26
#define ONRTNPOSITIONSUMMARY 27
#define ONRTNPOSITIONPROFIT 28
#define ONRSPQRYCURRENCY 29
#define ONRSPQRYTRADEMESSAGE 30
#define ONRTNTRADEMESSAGE 31
#define ONRSPQRYHISORDER 32
#define ONRSPQRYHISORDERPROCESS 33
#define ONRSPQRYHISMATCH 34
#define ONRSPQRYHISPOSITION 35
#define ONRSPQRYHISDELIVERY 36
#define ONRSPQRYACCOUNTCASHADJUST 37
#define ONRSPQRYBILL 38
#define ONRSPQRYACCOUNTFEERENT 39
#define ONRSPQRYACCOUNTMARGINRENT 40
#define ONRSPHKMARKETORDERINSERT 41
#define ONRSPHKMARKETORDERDELETE 42
#define ONHKMARKETQUOTENOTICE 43
#define ONRSPORDERLOCALREMOVE 44
#define ONRSPORDERLOCALINPUT 45
#define ONRSPORDERLOCALMODIFY 46
#define ONRSPORDERLOCALTRANSFER 47
#define ONRSPFILLLOCALINPUT 48
#define ONRSPFILLLOCALREMOVE 49


///-------------------------------------------------------------------------------------
///C++ SPI�Ļص���������ʵ��
///-------------------------------------------------------------------------------------

//API�ļ̳�ʵ��
class TdApi : public ITapTradeAPINotify
{
private:
	ITapTradeAPI* api;            //API����
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

		/**
		* @brief ���ӳɹ��ص�֪ͨ
		* @ingroup G_T_Login
		*/
	virtual void OnConnect();
	/**
	* @brief    ϵͳ��¼���̻ص���
	* @details    �˺���ΪLogin()��¼�����Ļص�������Login()�ɹ���������·���ӣ�Ȼ��API������������͵�¼��֤��Ϣ��
	*            ��¼�ڼ�����ݷ�������͵�¼�Ļ�����Ϣ���ݵ��˻ص������С�
	* @param[in] errorCode ���ش�����,0��ʾ�ɹ���
	* @param[in] loginRspInfo ��½Ӧ����Ϣ�����errorCode!=0����loginRspInfo=NULL��
	* @attention    �ûص����سɹ���˵���û���¼�ɹ������ǲ�����API׼����ϡ�
	* @ingroup G_T_Login
	*/
	virtual void OnRspLogin(int errorCode, TapAPITradeLoginRspInfo *loginRspInfo);
	/**
	* @brief    ������֤��ϵ��ʽ֪ͨ��
	* @details    ��¼��ɺ������Ҫ������֤��9.2.7��̨�������յ���ϵ��ʽ��֪ͨ������ѡ��֪ͨ��Ϣ��һ����ϵ��ʽ��������ߵ绰��
	*            �����Ͷ�����֤��Ȩ�루RequestVertificateCode����
	* @param[in] errorCode ���ش�����,0��ʾ�ɹ�������˻�û�а󶨶�����֤��ϵ��ʽ���򷵻�10016����
	* @param[in] isLast,��ʶ�Ƿ������һ����ϵ��Ϣ��
	* @param[in]  ��֤��ʽ��Ϣ�����errorCode!=0����ContactInfoΪ�ա�
	* @attention    �ûص����سɹ���˵����Ҫ������֤��������Ҫѡ��һ����ϵ��ʽȻ�����RequestVertificateCode��
	* @ingroup G_T_Login
	*/
	virtual void OnRtnContactInfo(int errorCode, char isLast, string ContactInfo);

	/**
	* @brief    �����Ͷ�����֤��Ӧ��
	* @details    �����ȡ������֤��Ȩ�룬��̨�����ʼ����߶��ţ�������Ӧ�𣬰�����������Լ���֤����Ч�ڡ�
	*
	* @param[in] sessionID ���������֤��ỰID��
	* @param[in]  errorCode ���û�а���ϵ������10016����.
	* @param[in]  rsp������֤����Ч�ڣ����뷵�أ��ڶ�����֤��Ч���ڣ������ظ����ö�����֤�룬���ǲ������������������֤�롣
	* @attention    �ûص����سɹ���˵����Ҫ������֤��������Ҫѡ��һ����ϵ��ʽȻ�����RequestVertificateCode��
	* @ingroup G_T_Login
	*/
	virtual void OnRspRequestVertificateCode(unsigned int sessionID, int errorCode, TapAPIRequestVertificateCodeRsp *rsp);

	/**
	* @brief    API�������ѻص�
	* @details    �˺���ΪLogin()��¼�ɹ�������������뵱ǰ����С��30�죬����лص����ѡ�
	* @param[in] date ����API��Ȩ�����ա�
	* @param[in] days ���ػ��м�����Ȩ���ڡ�
	* @attention    �ú����ص�����˵����Ȩ��һ����֮�ڵ��ڡ����򲻲����ûص���
	* @ingroup G_T_Login
	*/
	virtual void OnExpriationDate(string date, int days);

	/**
	* @brief    ֪ͨ�û�API׼��������
	* @details    ֻ���û��ص��յ��˾���֪ͨʱ���ܽ��к����ĸ����������ݲ�ѯ������\n
	*            �˻ص�������API�ܷ����������ı�־��
	* @attention ������ſ��Խ��к�����������
	* @ingroup G_T_Login
	*/
	virtual void OnAPIReady(int errorCode);
	/**
	* @brief    API�ͷ���ʧȥ���ӵĻص�
	* @details    ��APIʹ�ù������������߱��������������ʧȥ���Ӻ󶼻ᴥ���˻ص�֪ͨ�û���������������Ѿ��Ͽ���
	* @param[in] reasonCode �Ͽ�ԭ����롣
	* @ingroup G_T_Disconnect
	*/
	virtual void OnDisconnect(int reasonCode);
	/**
	* @brief ֪ͨ�û������޸Ľ��
	* @param[in] sessionID �޸�����ĻỰID,��ChangePassword���صĻỰID��Ӧ��
	* @param[in] errorCode ���ش����룬0��ʾ�ɹ���
	* @ingroup G_T_UserInfo
	*/
	virtual void OnRspChangePassword(unsigned int sessionID, int errorCode);

	/**
	* @brief ��֤�˻����뷴��
	* @param[in] sessionID �޸�����ĻỰID,��AuthPassword���صĻỰID��Ӧ��
	* @param[in] errorCode ���ش����룬0��ʾ�ɹ���
	* @ingroup G_T_UserInfo
	*/
	virtual void OnRspAuthPassword(unsigned int sessionID, int errorCode);

	/**
	* @brief    ����ϵͳ�������ں͵���LME������
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] info ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_UserRight
	*/

	virtual void OnRspQryTradingDate(unsigned int sessionID, int errorCode, TapAPITradingCalendarQryRsp *info);
	/**
	* @brief �����û�Ԥ����Ϣ����
	* @param[in] sessionID �����û�Ԥ����Ϣ�ĻỰID
	* @param[in] errorCode ���ش����룬0��ʾ�ɹ���
	* @param[in] info ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @note �ýӿ���δʵ��
	* @ingroup G_T_UserInfo
	*/
	virtual void OnRspSetReservedInfo(unsigned int sessionID, int errorCode, string info);


	/**
	* @brief    �����û���Ϣ
	* @details    �˻ص��ӿ����û����ز�ѯ���ʽ��˺ŵ���ϸ��Ϣ���û��б�Ҫ���õ����˺ű�ű���������Ȼ���ں����ĺ���������ʹ�á�
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] isLast ��ʾ�Ƿ������һ�����ݣ�
	* @param[in] info ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_AccountInfo
	*/
	virtual void OnRspQryAccount(unsigned int sessionID, unsigned int errorCode, char isLast, TapAPIAccountInfo *info);
	/**
	* @brief �����ʽ��˻����ʽ���Ϣ
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] isLast     ��ʾ�Ƿ������һ�����ݣ�
	* @param[in] info        ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_AccountDetails
	*/
	virtual void OnRspQryFund(unsigned int sessionID, int errorCode, char isLast, TapAPIFundData *info);
	/**
	* @brief    �û��ʽ�仯֪ͨ
	* @details    �û���ί�гɽ���������ʽ����ݵı仯�������Ҫ���û�ʵʱ������
	* @param[in] info        ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @note �������ע�������ݣ������趨Loginʱ��NoticeIgnoreFlag�����Ρ�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_AccountDetails
	*/
	virtual void OnRtnFund(TapAPIFundData *info);
	/**
	* @brief ����ϵͳ�еĽ�������Ϣ
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] isLast     ��ʾ�Ƿ������һ�����ݣ�
	* @param[in] info        ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_TradeSystem
	*/
	virtual void OnRspQryExchange(unsigned int sessionID, int errorCode, char isLast, TapAPIExchangeInfo *info);
	/**
	* @brief    ����ϵͳ��Ʒ����Ϣ
	* @details    �˻ص��ӿ��������û����صõ�������Ʒ����Ϣ��
	* @param[in] sessionID ����ĻỰID����GetAllCommodities()�������ض�Ӧ��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] isLast     ��ʾ�Ƿ������һ�����ݣ�
	* @param[in] info        ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_Commodity
	*/
	virtual void OnRspQryCommodity(unsigned int sessionID, int errorCode, char isLast, TapAPICommodityInfo *info);
	/**
	* @brief ����ϵͳ�к�Լ��Ϣ
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] isLast     ��ʾ�Ƿ������һ�����ݣ�
	* @param[in] info        ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_Contract
	*/
	virtual void OnRspQryContract(unsigned int sessionID, int errorCode, char isLast, TapAPITradeContractInfo *info);
	/**
	* @brief    ����������Լ��Ϣ
	* @details    ���û������µĺ�Լ����Ҫ���������ڽ���ʱ����з�����������º�Լʱ�����û����������Լ����Ϣ��
	* @param[in] info        ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_Contract
	*/
	virtual void OnRtnContract(TapAPITradeContractInfo *info);
	/**
* @brief    ��������Ӧ��
* @details    �µ����������ĵ�Ӧ���µ������д�Ӧ��ص�������µ�����ṹ��û����д��Լ�����ʽ��˺ţ�������ش���š�
		 * �������ĵ�������Ӧ���OnRtnOrder���ɹ�������OnRtnOrder�ص���
		 * sessionID��ʶ�����Ӧ��sessionID���Ա�ȷ���ñ�Ӧ���Ӧ������
		 *
* @param[in] sessionID ����ĻỰID��
* @param[in] errorCode �����롣0 ��ʾ�ɹ���
* @param[in] info ����Ӧ��������ͣ����������������ͺͶ�����Ϣָ�롣
		 * ������Ϣָ�벿������¿���Ϊ�գ����Ϊ�գ�����ͨ��SessiuonID�ҵ���Ӧ�����ȡ�������͡�
* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
* @ingroup G_T_TradeActions
*/
	virtual void OnRspOrderAction(unsigned int sessionID, int errorCode, TapAPIOrderActionRsp *info);
	/**
	* @brief ������ί�С����µĻ��������ط��µ����͹����ġ�
	* @details    ���������յ��ͻ��µ�ί�����ݺ�ͻᱣ�������ȴ�������ͬʱ���û�����һ��
	*            ��ί����Ϣ˵����������ȷ�������û������󣬷��ص���Ϣ�а�����ȫ����ί����Ϣ��
	*            ͬʱ��һ��������ʾ��ί�е�ί�кš�
	* @param[in] info ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @note �������ע�������ݣ������趨Loginʱ��NoticeIgnoreFlag�����Ρ�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_TradeActions
	*/
	virtual void OnRtnOrder(TapAPIOrderInfoNotice *info);
	/**
	* @brief    ���ز�ѯ��ί����Ϣ
	* @details    �����û���ѯ��ί�еľ�����Ϣ��
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] isLast ��ʾ�Ƿ������һ�����ݣ�
	* @param[in] info ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_TradeInfo
	*/
	virtual void OnRspQryOrder(unsigned int sessionID, int errorCode, char isLast, TapAPIOrderInfo *info);
	/**
	* @brief ���ز�ѯ��ί�б仯������Ϣ
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����룬��errorCode==0ʱ��infoָ�򷵻ص�ί�б仯���̽ṹ�壬��ȻΪNULL��
	* @param[in] isLast ��ʾ�Ƿ������һ�����ݣ�
	* @param[in] info ���ص�ί�б仯����ָ�롣
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_TradeInfo
	*/
	virtual void OnRspQryOrderProcess(unsigned int sessionID, int errorCode, char isLast, TapAPIOrderInfo *info);
	/**
	* @brief ���ز�ѯ�ĳɽ���Ϣ
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] isLast     ��ʾ�Ƿ������һ�����ݣ�
	* @param[in] info        ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_TradeInfo
	*/
	virtual void OnRspQryFill(unsigned int sessionID, int errorCode, char isLast, TapAPIFillInfo *info);
	/**
	* @brief    �������ĳɽ���Ϣ
	* @details    �û���ί�гɽ������û����ͳɽ���Ϣ��
	* @param[in] info        ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @note �������ע�������ݣ������趨Loginʱ��NoticeIgnoreFlag�����Ρ�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_TradeActions
	*/
	virtual void OnRtnFill(TapAPIFillInfo *info);
	/**
	* @brief ���ز�ѯ�ĳֲ�
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] isLast     ��ʾ�Ƿ������һ�����ݣ�
	* @param[in] info        ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_TradeInfo
	*/
	virtual void OnRspQryPosition(unsigned int sessionID, int errorCode, char isLast, TapAPIPositionInfo *info);
	/**
	* @brief �ֱֲ仯����֪ͨ
	* @param[in] info        ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @note �������ע�������ݣ������趨Loginʱ��NoticeIgnoreFlag�����Ρ�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_TradeActions
	*/
	virtual void OnRtnPosition(TapAPIPositionInfo *info);
	/**
	* @brief ���ز�ѯ�ĳֲֻ���
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] isLast     ��ʾ�Ƿ������һ�����ݣ�
	* @param[in] info        ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_TradeInfo
	*/
	virtual void OnRspQryPositionSummary(unsigned int sessionID, int errorCode, char isLast, TapAPIPositionSummary *info);

	/**
	* @brief �ֲֻ��ܱ仯����֪ͨ
	* @param[in] info        ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @note �������ע�������ݣ������趨Loginʱ��NoticeIgnoreFlag�����Ρ�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_TradeActions
	*/
	virtual void OnRtnPositionSummary(TapAPIPositionSummary *info);
	/**
	* @brief �ֲ�ӯ��֪ͨ
	* @param[in] info        ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @note �������ע�������ݣ������趨Loginʱ��NoticeIgnoreFlag�����Ρ�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_TradeActions
	*/
	virtual void OnRtnPositionProfit(TapAPIPositionProfitNotice *info);


	/**
	* @brief ����ϵͳ�еı�����Ϣ
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] isLast     ��ʾ�Ƿ������һ�����ݣ�
	* @param[in] info        ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_TradeSystem
	*/
	virtual void OnRspQryCurrency(unsigned int sessionID, int errorCode, char isLast, TapAPICurrencyInfo *info);

	/**
	* @brief    ������Ϣ֪ͨ
	* @details    ���ز�ѯ���û��ʽ�״̬��Ϣ����Ϣ˵�����û����ʽ�״̬���û���Ҫ��ϸ�鿴��Щ��Ϣ��
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] isLast     ��ʾ�Ƿ������һ�����ݣ�
	* @param[in] info        ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_AccountDetails
	*/
	virtual void OnRspQryTradeMessage(unsigned int sessionID, int errorCode, char isLast, TapAPITradeMessage *info);
	/**
	* @brief    ������Ϣ֪ͨ
	* @details    �û��ڽ��׹����п�����Ϊ�ʽ𡢳ֲ֡�ƽ�ֵ�״̬�䶯ʹ�˻�����ĳЩΣ��״̬������ĳЩ��Ҫ����Ϣ��Ҫ���û�֪ͨ��
	* @param[in] info        ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_AccountDetails
	*/
	virtual void OnRtnTradeMessage(TapAPITradeMessage *info);
	/**
	* @brief ��ʷί�в�ѯӦ��
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] isLast     ��ʾ�Ƿ������һ������
	* @param[in] info        ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_HisInfo
	*/
	virtual void OnRspQryHisOrder(unsigned int sessionID, int errorCode, char isLast, TapAPIHisOrderQryRsp *info);
	/**
	* @brief ��ʷί�����̲�ѯӦ��
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] isLast     ��ʾ�Ƿ������һ������
	* @param[in] info        ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_HisInfo
	*/
	virtual void OnRspQryHisOrderProcess(unsigned int sessionID, int errorCode, char isLast, TapAPIHisOrderProcessQryRsp *info);
	/**
	* @brief ��ʷ�ɽ���ѯӦ��
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] isLast     ��ʾ�Ƿ������һ������
	* @param[in] info        ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_HisInfo
	*/
	virtual void OnRspQryHisMatch(unsigned int sessionID, int errorCode, char isLast, TapAPIHisMatchQryRsp *info);
	/**
	* @brief ��ʷ�ֲֲ�ѯӦ��
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] isLast     ��ʾ�Ƿ������һ������
	* @param[in] info        ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_HisInfo
	*/
	virtual void OnRspQryHisPosition(unsigned int sessionID, int errorCode, char isLast, TapAPIHisPositionQryRsp *info);
	/**
	* @brief ��ʷ�����ѯӦ��
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] isLast     ��ʾ�Ƿ������һ������
	* @param[in] info        ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_HisInfo
	*/
	virtual void OnRspQryHisDelivery(unsigned int sessionID, int errorCode, char isLast, TapAPIHisDeliveryQryRsp *info);
	/**
	* @brief �ʽ������ѯӦ��
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] isLast     ��ʾ�Ƿ������һ������
	* @param[in] info        ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_HisInfo
	*/
	virtual void OnRspQryAccountCashAdjust(unsigned int sessionID, int errorCode, char isLast, TapAPIAccountCashAdjustQryRsp *info);
	/**
	* @brief ��ѯ�û��˵�Ӧ�� Add:2013.12.11
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] info        ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_Bill
	*/
	virtual void OnRspQryBill(unsigned int sessionID, int errorCode, char isLast, TapAPIBillQryRsp *info);
	/**
	* @brief ��ѯ�˻������Ѽ������ Add:2017.01.14
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] info        ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_Rent
	*/
	virtual void OnRspQryAccountFeeRent(unsigned int sessionID, int errorCode, char isLast, TapAPIAccountFeeRentQryRsp *info);
	/**
	* @brief ��ѯ�˻���֤�������� Add:2017.01.14
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] info        ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_Rent
	*/
	virtual void OnRspQryAccountMarginRent(unsigned int sessionID, int errorCode, char isLast, TapAPIAccountMarginRentQryRsp *info);

	/**
	* @brief �۽���������˫�߱���Ӧ�� Add:2017.08.29
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] info        ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_HKMarket
	*/
	virtual void OnRspHKMarketOrderInsert(unsigned int sessionID, int errorCode, TapAPIOrderMarketInsertRsp *info);

	/**
	* @brief �۽���������˫�߳���Ӧ�� Add:2017.08.29
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] info        ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_HKMarket
	*/
	virtual void OnRspHKMarketOrderDelete(unsigned int sessionID, int errorCode, TapAPIOrderMarketDeleteRsp *info);

	/**
	* @brief �۽���ѯ��֪ͨ Add:2017.08.29
	* @param[in] info        ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_HKMarket
	*/
	virtual void OnHKMarketQuoteNotice(TapAPIOrderQuoteMarketNotice *info);


	/**
	* @brief ����ɾ��Ӧ�� Add:2017.12.05
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] info        ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_LocalAction
	*/
	virtual void OnRspOrderLocalRemove(unsigned int sessionID, int errorCode, TapAPIOrderLocalRemoveRsp *info);

	/**
	* @brief ����¼��Ӧ�� Add:2017.12.05
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] info        ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_LocalAction
	*/
	virtual void OnRspOrderLocalInput(unsigned int sessionID, int errorCode, TapAPIOrderLocalInputRsp *info);

	/**
	* @brief �����޸�Ӧ�� Add:2017.12.05
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] info        ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_LocalAction
	*/
	virtual void OnRspOrderLocalModify(unsigned int sessionID, int errorCode, TapAPIOrderLocalModifyRsp *info);

	/**
	* @brief ����ת��Ӧ�� Add:2017.12.05
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] info        ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_LocalAction
	*/
	virtual void OnRspOrderLocalTransfer(unsigned int sessionID, int errorCode, TapAPIOrderLocalTransferRsp *info);

	/**
	* @brief �ɽ�¼��Ӧ�� Add:2017.12.05
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] info        ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_LocalAction
	*/
	virtual void OnRspFillLocalInput(unsigned int sessionID, int errorCode, TapAPIFillLocalInputRsp *info);

	/**
	* @brief ����ɾ��Ӧ�� Add:2017.12.05
	* @param[in] sessionID ����ĻỰID��
	* @param[in] errorCode �����롣0 ��ʾ�ɹ���
	* @param[in] info        ָ�򷵻ص���Ϣ�ṹ�塣��errorCode��Ϊ0ʱ��infoΪ�ա�
	* @attention ��Ҫ�޸ĺ�ɾ��info��ָʾ�����ݣ��������ý���������������Ч��
	* @ingroup G_T_LocalAction
	*/
	virtual void OnRspFillLocalRemove(unsigned int sessionID, int errorCode, TapAPIFillLocalRemoveRsp *info);



    //-------------------------------------------------------------------------------------
    //task������
    //-------------------------------------------------------------------------------------

	void processTask();

	void processConnect(Task *task);

	void processRspLogin(Task *task);

	void processRtnContactInfo(Task *task);

	void processRspRequestVertificateCode(Task *task);

	void processExpriationDate(Task *task);

	void processAPIReady(Task *task);

	void processDisconnect(Task *task);

	void processRspChangePassword(Task *task);

	void processRspAuthPassword(Task *task);

	void processRspQryTradingDate(Task *task);

	void processRspSetReservedInfo(Task *task);

	void processRspQryAccount(Task *task);

	void processRspQryFund(Task *task);

	void processRtnFund(Task *task);

	void processRspQryExchange(Task *task);

	void processRspQryCommodity(Task *task);

	void processRspQryContract(Task *task);

	void processRtnContract(Task *task);

	void processRspOrderAction(Task *task);

	void processRtnOrder(Task *task);

	void processRspQryOrder(Task *task);

	void processRspQryOrderProcess(Task *task);

	void processRspQryFill(Task *task);

	void processRtnFill(Task *task);

	void processRspQryPosition(Task *task);

	void processRtnPosition(Task *task);

	void processRspQryPositionSummary(Task *task);

	void processRtnPositionSummary(Task *task);

	void processRtnPositionProfit(Task *task);

	void processRspQryCurrency(Task *task);

	void processRspQryTradeMessage(Task *task);

	void processRtnTradeMessage(Task *task);

	void processRspQryHisOrder(Task *task);

	void processRspQryHisOrderProcess(Task *task);

	void processRspQryHisMatch(Task *task);

	void processRspQryHisPosition(Task *task);

	void processRspQryHisDelivery(Task *task);

	void processRspQryAccountCashAdjust(Task *task);

	void processRspQryBill(Task *task);

	void processRspQryAccountFeeRent(Task *task);

	void processRspQryAccountMarginRent(Task *task);

	void processRspHKMarketOrderInsert(Task *task);

	void processRspHKMarketOrderDelete(Task *task);

	void processHKMarketQuoteNotice(Task *task);

	void processRspOrderLocalRemove(Task *task);

	void processRspOrderLocalInput(Task *task);

	void processRspOrderLocalModify(Task *task);

	void processRspOrderLocalTransfer(Task *task);

	void processRspFillLocalInput(Task *task);

	void processRspFillLocalRemove(Task *task);



    //-------------------------------------------------------------------------------------
    //data���ص������������ֵ�
    //error���ص������Ĵ����ֵ�
    //id������id
    //last���Ƿ�Ϊ��󷵻�
    //i������
    //-------------------------------------------------------------------------------------
    
	virtual void onConnect() {};

	virtual void onRspLogin(int error, const dict &data) {};

	virtual void onRtnContactInfo(int error, char last, string ContactInfo) {};

	virtual void onRspRequestVertificateCode(unsigned int session, int error, const dict &data) {};

	virtual void onExpriationDate(string date, int days) {};

	virtual void onAPIReady(int error) {};

	virtual void onDisconnect(int reason) {};

	virtual void onRspChangePassword(unsigned int session, int error) {};

	virtual void onRspAuthPassword(unsigned int session, int error) {};

	virtual void onRspQryTradingDate(unsigned int session, int error, const dict &data) {};

	virtual void onRspSetReservedInfo(unsigned int session, int error, string info) {};

	virtual void onRspQryAccount(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRspQryFund(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRtnFund(const dict &data) {};

	virtual void onRspQryExchange(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRspQryCommodity(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRspQryContract(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRtnContract(const dict &data) {};

	virtual void onRspOrderAction(unsigned int session, int error, const dict &data) {};

	virtual void onRtnOrder(const dict &data) {};

	virtual void onRspQryOrder(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRspQryOrderProcess(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRspQryFill(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRtnFill(const dict &data) {};

	virtual void onRspQryPosition(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRtnPosition(const dict &data) {};

	virtual void onRspQryPositionSummary(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRtnPositionSummary(const dict &data) {};

	virtual void onRtnPositionProfit(const dict &data) {};

	virtual void onRspQryCurrency(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRspQryTradeMessage(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRtnTradeMessage(const dict &data) {};

	virtual void onRspQryHisOrder(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRspQryHisOrderProcess(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRspQryHisMatch(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRspQryHisPosition(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRspQryHisDelivery(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRspQryAccountCashAdjust(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRspQryBill(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRspQryAccountFeeRent(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRspQryAccountMarginRent(unsigned int session, int error, char last, const dict &data) {};

	virtual void onRspHKMarketOrderInsert(unsigned int session, int error, const dict &data) {};

	virtual void onRspHKMarketOrderDelete(unsigned int session, int error, const dict &data) {};

	virtual void onHKMarketQuoteNotice(const dict &data) {};

	virtual void onRspOrderLocalRemove(unsigned int session, int error, const dict &data) {};

	virtual void onRspOrderLocalInput(unsigned int session, int error, const dict &data) {};

	virtual void onRspOrderLocalModify(unsigned int session, int error, const dict &data) {};

	virtual void onRspOrderLocalTransfer(unsigned int session, int error, const dict &data) {};

	virtual void onRspFillLocalInput(unsigned int session, int error, const dict &data) {};

	virtual void onRspFillLocalRemove(unsigned int session, int error, const dict &data) {};



    //-------------------------------------------------------------------------------------
    //req:���������������ֵ�
    //-------------------------------------------------------------------------------------
	void CreateITapTradeAPI(const dict &req, int &iResult);

	void release();

	void init();

	int exit();

	string getITapTradeAPIVersion();

	int setITapTradeAPIDataPath(string path);

	int setITapTradeAPILogLevel(string level); //1

	int setHostAddress(string IP, unsigned short port);

	int login(const dict &req);

	int requestVertificateCode(unsigned int *sessionID, string ContactInfo); //2

	int setVertificateCode(string VertificateCode); //3

	int disconnect();

	int authPassword(unsigned int *sessionID, const dict &req);

	int haveCertainRight(int rightID);

	int insertOrder(unsigned int *sessionID, string *ClientOrderNo, TapAPINewOrder *order); //7

	int cancelOrder(unsigned int *sessionID, TapAPIOrderCancelReq *order); //8





	int qryTradingDate(unsigned int *session);

	int qryAccount(unsigned int *session, const dict &data);

	int qryFund(unsigned int *session, const dict &data);

	int qryExchange(unsigned int *session);

	int qryCommodity(unsigned int *session);

	int qryContract(unsigned int *session, const dict &data);

	int qryOrder(unsigned int *session, const dict &data);

	int qryOrderProcess(unsigned int *session, const dict &data);

	int qryFill(unsigned int *session, const dict &data);

	int qryPosition(unsigned int *session, const dict &data);

	int qryPositionSummary(unsigned int *session, const dict &data);

	int qryCurrency(unsigned int *session);

	int qryAccountCashAdjust(unsigned int *session, const dict &data);

	int qryTradeMessage(unsigned int *session, const dict &data);

	int qryBill(unsigned int *session, const dict &data);

	int qryHisOrder(unsigned int *session, const dict &data);

	int qryHisOrderProcess(unsigned int *session, const dict &data);

	int qryHisMatch(unsigned int *session, const dict &data);

	int qryHisPosition(unsigned int *session, const dict &data);

	int qryHisDelivery(unsigned int *session, const dict &data);

	int qryAccountFeeRent(unsigned int *session, const dict &data);

	int qryAccountMarginRent(unsigned int *session, const dict &data);

	//------------
	// int setAPINotify(ITapTradeAPINotify *pSpi); 

	//int changePassword(unsigned int *sessionID, TapAPIChangePasswordReq *req);

	//int setReservedInfo(unsigned int *sessionID, string info);

	//int amendOrder(unsigned int *sessionID, TapAPIAmendOrder *order); //9

	//int activateOrder(unsigned int * sessionID, TapAPIOrderActivateReq * order);

	//int insertHKMarketOrder(unsigned int *sessionID, string *ClientBuyOrderNo, string *ClientSellOrderNo, TapAPIOrderMarketInsertReq *order);

	//int cancelHKMarketOrder(unsigned int *sessionID, TapAPIOrderMarketDeleteReq *order);

	//int orderLocalRemove(unsigned int *sessionID, TapAPIOrderLocalRemoveReq *order);

	//int orderLocalInput(unsigned int *sessionID, TapAPIOrderLocalInputReq *order);

	//int orderLocalModify(unsigned int *sessionID, TapAPIOrderLocalModifyReq *order);

	//int orderLocalTransfer(unsigned int *sessionID, TapAPIOrderLocalTransferReq *order);

	//int fillLocalInput(unsigned int *sessionID, TapAPIFillLocalInputReq *fill);

	//int fillLocalRemove(unsigned int *sessionID, TapAPIFillLocalRemoveReq *fill);
};
