//˵������
/*
����CTP API�к��ʽ�ת����صĺ���̫�࣬
ͬʱҲ�Ѿ��д����Ŀͻ���֧����Щ���ܣ�
��������Python��װ����ʱѡ��ֻ֧�ֽ��׹���
*/


//ϵͳ
#ifdef WIN32
#include "stdafx.h"
#endif
#include <string>
#include <queue>

//Boost
#define BOOST_PYTHON_STATIC_LIB
#include <boost/python/module.hpp>	//python��װ
#include <boost/python/def.hpp>		//python��װ
#include <boost/python/dict.hpp>	//python��װ
#include <boost/python/object.hpp>	//python��װ
#include <boost/python.hpp>			//python��װ
#include <boost/thread.hpp>			//������е��̹߳���
#include <boost/bind.hpp>			//������е��̹߳���
#include <boost/any.hpp>			//������е�����ʵ��

//API
#include "ThostFtdcTraderApi.h"

//�����ռ�
using namespace std;
using namespace boost::python;
using namespace boost;

//����
#define ONFRONTCONNECTED 1
#define ONFRONTDISCONNECTED 2
#define ONHEARTBEATWARNING 3
#define ONRSPAUTHENTICATE 4
#define ONRSPUSERLOGIN 5
#define ONRSPUSERLOGOUT 6
#define ONRSPUSERPASSWORDUPDATE 7
#define ONRSPTRADINGACCOUNTPASSWORDUPDATE 8
#define ONRSPORDERINSERT 9
#define ONRSPPARKEDORDERINSERT 10
#define ONRSPPARKEDORDERACTION 11
#define ONRSPORDERACTION 12
#define ONRSPQUERYMAXORDERVOLUME 13
#define ONRSPSETTLEMENTINFOCONFIRM 14
#define ONRSPREMOVEPARKEDORDER 15
#define ONRSPREMOVEPARKEDORDERACTION 16
#define ONRSPEXECORDERINSERT 17
#define ONRSPEXECORDERACTION 18
#define ONRSPFORQUOTEINSERT 19
#define ONRSPQUOTEINSERT 20
#define ONRSPQUOTEACTION 21
#define ONRSPBATCHORDERACTION 22
#define ONRSPOPTIONSELFCLOSEINSERT 23
#define ONRSPOPTIONSELFCLOSEACTION 24
#define ONRSPTRANSFUND 25
#define ONRSPQRYORDER 26
#define ONRSPQRYTRADE 27
#define ONRSPQRYINVESTORPOSITION 28
#define ONRSPQRYTRADINGACCOUNT 29
#define ONRSPQRYINVESTOR 30
#define ONRSPQRYTRADINGCODE 31
#define ONRSPQRYINSTRUMENTMARGINRATE 32
#define ONRSPQRYINSTRUMENTCOMMISSIONRATE 33
#define ONRSPQRYEXCHANGE 34
#define ONRSPQRYPRODUCT 35
#define ONRSPQRYINSTRUMENT 36
#define ONRSPQRYDEPTHMARKETDATA 37
#define ONRSPQRYSETTLEMENTINFO 38
#define ONRSPQRYINSTRUMENTSTATUS 39
#define ONRSPQRYTRANSFERBANK 40
#define ONRSPQRYINVESTORPOSITIONDETAIL 41
#define ONRSPQRYNOTICE 42
#define ONRSPQRYSETTLEMENTINFOCONFIRM 43
#define ONRSPQRYINVESTORPOSITIONCOMBINEDETAIL 44
#define ONRSPQRYCFMMCTRADINGACCOUNTKEY 45
#define ONRSPQRYEWARRANTOFFSET 46
#define ONRSPQRYINVESTORPRODUCTGROUPMARGIN 47
#define ONRSPQRYEXCHANGEMARGINRATE 48
#define ONRSPQRYEXCHANGEMARGINRATEADJUST 49
#define ONRSPQRYEXCHANGERATE 50
#define ONRSPQRYSECAGENTACIDMAP 51
#define ONRSPQRYOPTIONINSTRTRADECOST 52
#define ONRSPQRYOPTIONINSTRCOMMRATE 53
#define ONRSPQRYEXECORDER 54
#define ONRSPQRYFORQUOTE 55
#define ONRSPQRYQUOTE 56
#define ONRSPQRYOPTIONSELFCLOSE 57
#define ONRSPQRYTRANSFERSERIAL 58
#define ONRSPQRYACCOUNTREGISTER 59
#define ONRSPERROR 60
#define ONRTNORDER 61
#define ONRTNTRADE 62
#define ONERRRTNORDERINSERT 63
#define ONERRRTNORDERACTION 64
#define ONRTNINSTRUMENTSTATUS 65
#define ONRTNTRADINGNOTICE 66
#define ONRTNERRORCONDITIONALORDER 67
#define ONRTNEXECORDER 68
#define ONERRRTNEXECORDERINSERT 69
#define ONERRRTNEXECORDERACTION 70
#define ONERRRTNFORQUOTEINSERT 71
#define ONRTNQUOTE 72
#define ONERRRTNQUOTEINSERT 73
#define ONERRRTNQUOTEACTION 74
#define ONRTNFORQUOTERSP 75
#define ONERRRTNBATCHORDERACTION 76
#define ONRTNOPTIONSELFCLOSE 77
#define ONERRRTNOPTIONSELFCLOSEINSERT 78
#define ONERRRTNOPTIONSELFCLOSEACTION 79
#define ONRSPQRYCONTRACTBANK 80
#define ONRSPQRYPARKEDORDER 81
#define ONRSPQRYPARKEDORDERACTION 82
#define ONRSPQRYTRADINGNOTICE 83
#define ONRSPQRYBROKERTRADINGPARAMS 84
#define ONRSPQRYBROKERTRADINGALGOS 85
#define ONRTNFROMBANKTOFUTUREBYBANK 86
#define ONRTNFROMFUTURETOBANKBYBANK 87
#define ONRTNREPEALFROMBANKTOFUTUREBYBANK 88
#define ONRTNREPEALFROMFUTURETOBANKBYBANK 89
#define ONRTNFROMBANKTOFUTUREBYFUTURE 90
#define ONRTNFROMFUTURETOBANKBYFUTURE 91
#define ONRTNREPEALFROMBANKTOFUTUREBYFUTUREMANUAL 92
#define ONRTNREPEALFROMFUTURETOBANKBYFUTUREMANUAL 93
#define ONRTNQUERYBANKBALANCEBYFUTURE 94
#define ONERRRTNBANKTOFUTUREBYFUTURE 95
#define ONERRRTNFUTURETOBANKBYFUTURE 96
#define ONERRRTNREPEALBANKTOFUTUREBYFUTUREMANUAL 97
#define ONERRRTNREPEALFUTURETOBANKBYFUTUREMANUAL 98
#define ONERRRTNQUERYBANKBALANCEBYFUTURE 99
#define ONRTNREPEALFROMBANKTOFUTUREBYFUTURE 100
#define ONRTNREPEALFROMFUTURETOBANKBYFUTURE 101
#define ONRSPFROMBANKTOFUTUREBYFUTURE 102
#define ONRSPFROMFUTURETOBANKBYFUTURE 103
#define ONRSPQUERYBANKACCOUNTMONEYBYFUTURE 104
#define ONRTNOPENACCOUNTBYBANK 105
#define ONRTNCANCELACCOUNTBYBANK 106
#define ONRTNCHANGEACCOUNTBYBANK 107


///-------------------------------------------------------------------------------------
///API�еĲ������
///-------------------------------------------------------------------------------------

//GILȫ�����򻯻�ȡ�ã�
//���ڰ���C++�̻߳��GIL�����Ӷ���ֹpython����
class PyLock
{
private:
	PyGILState_STATE gil_state;

public:
	//��ĳ�����������д����ö���ʱ�����GIL��
	PyLock()
	{
		gil_state = PyGILState_Ensure();
	}

	//��ĳ��������ɺ����ٸö���ʱ�����GIL��
	~PyLock()
	{
		PyGILState_Release(gil_state);
	}
};


//����ṹ��
struct Task
{
	int task_name;		//�ص��������ƶ�Ӧ�ĳ���
	any task_data;		//���ݽṹ��
	any task_error;		//����ṹ��
	int task_id;		//����id
	bool task_last;		//�Ƿ�Ϊ��󷵻�
};


///�̰߳�ȫ�Ķ���
template<typename Data>

class ConcurrentQueue
{
private:
	queue<Data> the_queue;								//��׼�����
	mutable mutex the_mutex;							//boost������
	condition_variable the_condition_variable;			//boost��������

public:

	//�����µ�����
	void push(Data const& data)
	{
		mutex::scoped_lock lock(the_mutex);				//��ȡ������
		the_queue.push(data);							//������д�������
		lock.unlock();									//�ͷ���
		the_condition_variable.notify_one();			//֪ͨ���������ȴ����߳�
	}

	//�������Ƿ�Ϊ��
	bool empty() const
	{
		mutex::scoped_lock lock(the_mutex);
		return the_queue.empty();
	}

	//ȡ��
	Data wait_and_pop()
	{
		mutex::scoped_lock lock(the_mutex);

		while (the_queue.empty())						//������Ϊ��ʱ
		{
			the_condition_variable.wait(lock);			//�ȴ���������֪ͨ
		}

		Data popped_value = the_queue.front();			//��ȡ�����е����һ������
		the_queue.pop();								//ɾ��������
		return popped_value;							//���ظ�����
	}

};


//���ֵ��л�ȡĳ����ֵ��Ӧ������������ֵ������ṹ������ֵ��
void getInt(dict d, string key, int* value);


//���ֵ��л�ȡĳ����ֵ��Ӧ�ĸ�����������ֵ������ṹ������ֵ��
void getDouble(dict d, string key, double* value);


//���ֵ��л�ȡĳ����ֵ��Ӧ���ַ�������ֵ������ṹ������ֵ��
void getChar(dict d, string key, char* value);


//���ֵ��л�ȡĳ����ֵ��Ӧ���ַ���������ֵ������ṹ������ֵ��
void getStr(dict d, string key, char* value);


///-------------------------------------------------------------------------------------
///C++ SPI�Ļص���������ʵ��
///-------------------------------------------------------------------------------------

//API�ļ̳�ʵ��
class TdApi : public CThostFtdcTraderSpi
{
private:
	CThostFtdcTraderApi* api;			//API����
	thread *task_thread;				//�����߳�ָ�루��python���������ݣ�
	ConcurrentQueue<Task> task_queue;	//�������

public:
	TdApi()
	{
		function0<void> f = boost::bind(&TdApi::processTask, this);
		thread t(f);
		this->task_thread = &t;
	};

	~TdApi()
	{
	};

	//-------------------------------------------------------------------------------------
	//API�ص�����
	//-------------------------------------------------------------------------------------

	///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
	virtual void OnFrontConnected();

	///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
	///@param nReason ����ԭ��
	///        0x1001 �����ʧ��
	///        0x1002 ����дʧ��
	///        0x2001 ����������ʱ
	///        0x2002 ��������ʧ��
	///        0x2003 �յ�������
	virtual void OnFrontDisconnected(int nReason);

	///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
	///@param nTimeLapse �����ϴν��ձ��ĵ�ʱ��
	virtual void OnHeartBeatWarning(int nTimeLapse);

	///�ͻ�����֤��Ӧ
	virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///��¼������Ӧ
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�ǳ�������Ӧ
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�û��������������Ӧ
	virtual void OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�ʽ��˻��������������Ӧ
	virtual void OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///����¼��������Ӧ
	virtual void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///Ԥ��¼��������Ӧ
	virtual void OnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///Ԥ�񳷵�¼��������Ӧ
	virtual void OnRspParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///��������������Ӧ
	virtual void OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///��ѯ��󱨵�������Ӧ
	virtual void OnRspQueryMaxOrderVolume(CThostFtdcQueryMaxOrderVolumeField *pQueryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///Ͷ���߽�����ȷ����Ӧ
	virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///ɾ��Ԥ����Ӧ
	virtual void OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///ɾ��Ԥ�񳷵���Ӧ
	virtual void OnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///ִ������¼��������Ӧ
	virtual void OnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///ִ���������������Ӧ
	virtual void OnRspExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///ѯ��¼��������Ӧ
	virtual void OnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///����¼��������Ӧ
	virtual void OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///���۲���������Ӧ
	virtual void OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///������������������Ӧ
	virtual void OnRspBatchOrderAction(CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///��Ȩ�ԶԳ�¼��������Ӧ
	virtual void OnRspOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///��Ȩ�ԶԳ����������Ӧ
	virtual void OnRspOptionSelfCloseAction(CThostFtdcInputOptionSelfCloseActionField *pInputOptionSelfCloseAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///������ļ��ʽ�ת����Ӧ
	virtual void OnRspTransFund(CThostFtdcTransFundField *pTransFund, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�����ѯ������Ӧ
	virtual void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�����ѯ�ɽ���Ӧ
	virtual void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�����ѯͶ���ֲ߳���Ӧ
	virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�����ѯ�ʽ��˻���Ӧ
	virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�����ѯͶ������Ӧ
	virtual void OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�����ѯ���ױ�����Ӧ
	virtual void OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�����ѯ��Լ��֤������Ӧ
	virtual void OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�����ѯ��Լ����������Ӧ
	virtual void OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�����ѯ��������Ӧ
	virtual void OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�����ѯ��Ʒ��Ӧ
	virtual void OnRspQryProduct(CThostFtdcProductField *pProduct, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�����ѯ��Լ��Ӧ
	virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�����ѯ������Ӧ
	virtual void OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�����ѯͶ���߽�������Ӧ
	virtual void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�����ѯ��Լ״̬��Ӧ
	virtual void OnRspQryInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�����ѯת��������Ӧ
	virtual void OnRspQryTransferBank(CThostFtdcTransferBankField *pTransferBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�����ѯͶ���ֲ߳���ϸ��Ӧ
	virtual void OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�����ѯ�ͻ�֪ͨ��Ӧ
	virtual void OnRspQryNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�����ѯ������Ϣȷ����Ӧ
	virtual void OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�����ѯͶ���ֲ߳���ϸ��Ӧ
	virtual void OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///��ѯ��֤����ϵͳ���͹�˾�ʽ��˻���Կ��Ӧ
	virtual void OnRspQryCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField *pCFMMCTradingAccountKey, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�����ѯ�ֵ��۵���Ϣ��Ӧ
	virtual void OnRspQryEWarrantOffset(CThostFtdcEWarrantOffsetField *pEWarrantOffset, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�����ѯͶ����Ʒ��/��Ʒ�ֱ�֤����Ӧ
	virtual void OnRspQryInvestorProductGroupMargin(CThostFtdcInvestorProductGroupMarginField *pInvestorProductGroupMargin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�����ѯ��������֤������Ӧ
	virtual void OnRspQryExchangeMarginRate(CThostFtdcExchangeMarginRateField *pExchangeMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�����ѯ������������֤������Ӧ
	virtual void OnRspQryExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField *pExchangeMarginRateAdjust, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�����ѯ������Ӧ
	virtual void OnRspQryExchangeRate(CThostFtdcExchangeRateField *pExchangeRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�����ѯ�����������Ա����Ȩ����Ӧ
	virtual void OnRspQrySecAgentACIDMap(CThostFtdcSecAgentACIDMapField *pSecAgentACIDMap, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�����ѯ��Ȩ���׳ɱ���Ӧ
	virtual void OnRspQryOptionInstrTradeCost(CThostFtdcOptionInstrTradeCostField *pOptionInstrTradeCost, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�����ѯ��Ȩ��Լ��������Ӧ
	virtual void OnRspQryOptionInstrCommRate(CThostFtdcOptionInstrCommRateField *pOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�����ѯִ��������Ӧ
	virtual void OnRspQryExecOrder(CThostFtdcExecOrderField *pExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�����ѯѯ����Ӧ
	virtual void OnRspQryForQuote(CThostFtdcForQuoteField *pForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�����ѯ������Ӧ
	virtual void OnRspQryQuote(CThostFtdcQuoteField *pQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�����ѯ��Ȩ�ԶԳ���Ӧ
	virtual void OnRspQryOptionSelfClose(CThostFtdcOptionSelfCloseField *pOptionSelfClose, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�����ѯת����ˮ��Ӧ
	virtual void OnRspQryTransferSerial(CThostFtdcTransferSerialField *pTransferSerial, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�����ѯ����ǩԼ��ϵ��Ӧ
	virtual void OnRspQryAccountregister(CThostFtdcAccountregisterField *pAccountregister, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///����Ӧ��
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///����֪ͨ
	virtual void OnRtnOrder(CThostFtdcOrderField *pOrder) ;

	///�ɽ�֪ͨ
	virtual void OnRtnTrade(CThostFtdcTradeField *pTrade) ;

	///����¼�����ر�
	virtual void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo) ;

	///������������ر�
	virtual void OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo) ;

	///��Լ����״̬֪ͨ
	virtual void OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus) ;

	///����֪ͨ
	virtual void OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo) ;

	///��ʾ������У�����
	virtual void OnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder) ;

	///ִ������֪ͨ
	virtual void OnRtnExecOrder(CThostFtdcExecOrderField *pExecOrder) ;

	///ִ������¼�����ر�
	virtual void OnErrRtnExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo) ;

	///ִ�������������ر�
	virtual void OnErrRtnExecOrderAction(CThostFtdcExecOrderActionField *pExecOrderAction, CThostFtdcRspInfoField *pRspInfo) ;

	///ѯ��¼�����ر�
	virtual void OnErrRtnForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo) ;

	///����֪ͨ
	virtual void OnRtnQuote(CThostFtdcQuoteField *pQuote) ;

	///����¼�����ر�
	virtual void OnErrRtnQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo) ;

	///���۲�������ر�
	virtual void OnErrRtnQuoteAction(CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo) ;

	///ѯ��֪ͨ
	virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) ;

	///����������������ر�
	virtual void OnErrRtnBatchOrderAction(CThostFtdcBatchOrderActionField *pBatchOrderAction, CThostFtdcRspInfoField *pRspInfo) ;

	///��Ȩ�ԶԳ�֪ͨ
	virtual void OnRtnOptionSelfClose(CThostFtdcOptionSelfCloseField *pOptionSelfClose) ;

	///��Ȩ�ԶԳ�¼�����ر�
	virtual void OnErrRtnOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CThostFtdcRspInfoField *pRspInfo) ;

	///��Ȩ�ԶԳ��������ر�
	virtual void OnErrRtnOptionSelfCloseAction(CThostFtdcOptionSelfCloseActionField *pOptionSelfCloseAction, CThostFtdcRspInfoField *pRspInfo) ;

	///�����ѯǩԼ������Ӧ
	virtual void OnRspQryContractBank(CThostFtdcContractBankField *pContractBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�����ѯԤ����Ӧ
	virtual void OnRspQryParkedOrder(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�����ѯԤ�񳷵���Ӧ
	virtual void OnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�����ѯ����֪ͨ��Ӧ
	virtual void OnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�����ѯ���͹�˾���ײ�����Ӧ
	virtual void OnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField *pBrokerTradingParams, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�����ѯ���͹�˾�����㷨��Ӧ
	virtual void OnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField *pBrokerTradingAlgos, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///���з��������ʽ�ת�ڻ�֪ͨ
	virtual void OnRtnFromBankToFutureByBank(CThostFtdcRspTransferField *pRspTransfer) ;

	///���з����ڻ��ʽ�ת����֪ͨ
	virtual void OnRtnFromFutureToBankByBank(CThostFtdcRspTransferField *pRspTransfer) ;

	///���з����������ת�ڻ�֪ͨ
	virtual void OnRtnRepealFromBankToFutureByBank(CThostFtdcRspRepealField *pRspRepeal) ;

	///���з�������ڻ�ת����֪ͨ
	virtual void OnRtnRepealFromFutureToBankByBank(CThostFtdcRspRepealField *pRspRepeal) ;

	///�ڻ����������ʽ�ת�ڻ�֪ͨ
	virtual void OnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField *pRspTransfer) ;

	///�ڻ������ڻ��ʽ�ת����֪ͨ
	virtual void OnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField *pRspTransfer) ;

	///ϵͳ����ʱ�ڻ����ֹ������������ת�ڻ��������д�����Ϻ��̷��ص�֪ͨ
	virtual void OnRtnRepealFromBankToFutureByFutureManual(CThostFtdcRspRepealField *pRspRepeal) ;

	///ϵͳ����ʱ�ڻ����ֹ���������ڻ�ת�����������д�����Ϻ��̷��ص�֪ͨ
	virtual void OnRtnRepealFromFutureToBankByFutureManual(CThostFtdcRspRepealField *pRspRepeal) ;

	///�ڻ������ѯ�������֪ͨ
	virtual void OnRtnQueryBankBalanceByFuture(CThostFtdcNotifyQueryAccountField *pNotifyQueryAccount) ;

	///�ڻ����������ʽ�ת�ڻ�����ر�
	virtual void OnErrRtnBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo) ;

	///�ڻ������ڻ��ʽ�ת���д���ر�
	virtual void OnErrRtnFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo) ;

	///ϵͳ����ʱ�ڻ����ֹ������������ת�ڻ�����ر�
	virtual void OnErrRtnRepealBankToFutureByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo) ;

	///ϵͳ����ʱ�ڻ����ֹ���������ڻ�ת���д���ر�
	virtual void OnErrRtnRepealFutureToBankByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo) ;

	///�ڻ������ѯ����������ر�
	virtual void OnErrRtnQueryBankBalanceByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo) ;

	///�ڻ������������ת�ڻ��������д�����Ϻ��̷��ص�֪ͨ
	virtual void OnRtnRepealFromBankToFutureByFuture(CThostFtdcRspRepealField *pRspRepeal) ;

	///�ڻ���������ڻ�ת�����������д�����Ϻ��̷��ص�֪ͨ
	virtual void OnRtnRepealFromFutureToBankByFuture(CThostFtdcRspRepealField *pRspRepeal) ;

	///�ڻ����������ʽ�ת�ڻ�Ӧ��
	virtual void OnRspFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�ڻ������ڻ��ʽ�ת����Ӧ��
	virtual void OnRspFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///�ڻ������ѯ�������Ӧ��
	virtual void OnRspQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///���з������ڿ���֪ͨ
	virtual void OnRtnOpenAccountByBank(CThostFtdcOpenAccountField *pOpenAccount) ;

	///���з�����������֪ͨ
	virtual void OnRtnCancelAccountByBank(CThostFtdcCancelAccountField *pCancelAccount) ;

	///���з����������˺�֪ͨ
	virtual void OnRtnChangeAccountByBank(CThostFtdcChangeAccountField *pChangeAccount) ;

	//-------------------------------------------------------------------------------------
	//task������
	//-------------------------------------------------------------------------------------

	void processTask();

	void processFrontConnected(Task task);

	void processFrontDisconnected(Task task);

	void processHeartBeatWarning(Task task);

	void processRspAuthenticate(Task task);

	void processRspUserLogin(Task task);

	void processRspUserLogout(Task task);

	void processRspUserPasswordUpdate(Task task);

	void processRspTradingAccountPasswordUpdate(Task task);

	void processRspOrderInsert(Task task);

	void processRspParkedOrderInsert(Task task);

	void processRspParkedOrderAction(Task task);

	void processRspOrderAction(Task task);

	void processRspQueryMaxOrderVolume(Task task);

	void processRspSettlementInfoConfirm(Task task);

	void processRspRemoveParkedOrder(Task task);

	void processRspRemoveParkedOrderAction(Task task);

	void processRspExecOrderInsert(Task task);

	void processRspExecOrderAction(Task task);

	void processRspForQuoteInsert(Task task);

	void processRspQuoteInsert(Task task);

	void processRspQuoteAction(Task task);

	void processRspBatchOrderAction(Task task);

	void processRspOptionSelfCloseInsert(Task task);

	void processRspOptionSelfCloseAction(Task task);

	void processRspTransFund(Task task);

	void processRspQryOrder(Task task);

	void processRspQryTrade(Task task);

	void processRspQryInvestorPosition(Task task);

	void processRspQryTradingAccount(Task task);

	void processRspQryInvestor(Task task);

	void processRspQryTradingCode(Task task);

	void processRspQryInstrumentMarginRate(Task task);

	void processRspQryInstrumentCommissionRate(Task task);

	void processRspQryExchange(Task task);

	void processRspQryProduct(Task task);

	void processRspQryInstrument(Task task);

	void processRspQryDepthMarketData(Task task);

	void processRspQrySettlementInfo(Task task);

	void processRspQryInstrumentStatus(Task task);

	void processRspQryTransferBank(Task task);

	void processRspQryInvestorPositionDetail(Task task);

	void processRspQryNotice(Task task);

	void processRspQrySettlementInfoConfirm(Task task);

	void processRspQryInvestorPositionCombineDetail(Task task);

	void processRspQryCFMMCTradingAccountKey(Task task);

	void processRspQryEWarrantOffset(Task task);

	void processRspQryInvestorProductGroupMargin(Task task);

	void processRspQryExchangeMarginRate(Task task);

	void processRspQryExchangeMarginRateAdjust(Task task);

	void processRspQryExchangeRate(Task task);

	void processRspQrySecAgentACIDMap(Task task);

	void processRspQryOptionInstrTradeCost(Task task);

	void processRspQryOptionInstrCommRate(Task task);

	void processRspQryExecOrder(Task task);

	void processRspQryForQuote(Task task);

	void processRspQryQuote(Task task);

	void processRspQryOptionSelfClose(Task task);

	void processRspQryTransferSerial(Task task);

	void processRspQryAccountregister(Task task);

	void processRspError(Task task);

	void processRtnOrder(Task task);

	void processRtnTrade(Task task);

	void processErrRtnOrderInsert(Task task);

	void processErrRtnOrderAction(Task task);

	void processRtnInstrumentStatus(Task task);

	void processRtnTradingNotice(Task task);

	void processRtnErrorConditionalOrder(Task task);

	void processRtnExecOrder(Task task);

	void processErrRtnExecOrderInsert(Task task);

	void processErrRtnExecOrderAction(Task task);

	void processErrRtnForQuoteInsert(Task task);

	void processRtnQuote(Task task);

	void processErrRtnQuoteInsert(Task task);

	void processErrRtnQuoteAction(Task task);

	void processRtnForQuoteRsp(Task task);

	void processErrRtnBatchOrderAction(Task task);

	void processRtnOptionSelfClose(Task task);

	void processErrRtnOptionSelfCloseInsert(Task task);

	void processErrRtnOptionSelfCloseAction(Task task);

	void processRspQryContractBank(Task task);

	void processRspQryParkedOrder(Task task);

	void processRspQryParkedOrderAction(Task task);

	void processRspQryTradingNotice(Task task);

	void processRspQryBrokerTradingParams(Task task);

	void processRspQryBrokerTradingAlgos(Task task);

	void processRtnFromBankToFutureByBank(Task task);

	void processRtnFromFutureToBankByBank(Task task);

	void processRtnRepealFromBankToFutureByBank(Task task);

	void processRtnRepealFromFutureToBankByBank(Task task);

	void processRtnFromBankToFutureByFuture(Task task);

	void processRtnFromFutureToBankByFuture(Task task);

	void processRtnRepealFromBankToFutureByFutureManual(Task task);

	void processRtnRepealFromFutureToBankByFutureManual(Task task);

	void processRtnQueryBankBalanceByFuture(Task task);

	void processErrRtnBankToFutureByFuture(Task task);

	void processErrRtnFutureToBankByFuture(Task task);

	void processErrRtnRepealBankToFutureByFutureManual(Task task);

	void processErrRtnRepealFutureToBankByFutureManual(Task task);

	void processErrRtnQueryBankBalanceByFuture(Task task);

	void processRtnRepealFromBankToFutureByFuture(Task task);

	void processRtnRepealFromFutureToBankByFuture(Task task);

	void processRspFromBankToFutureByFuture(Task task);

	void processRspFromFutureToBankByFuture(Task task);

	void processRspQueryBankAccountMoneyByFuture(Task task);

	void processRtnOpenAccountByBank(Task task);

	void processRtnCancelAccountByBank(Task task);

	void processRtnChangeAccountByBank(Task task);

	//-------------------------------------------------------------------------------------
	//data���ص������������ֵ�
	//error���ص������Ĵ����ֵ�
	//id������id
	//last���Ƿ�Ϊ��󷵻�
	//i������
	//-------------------------------------------------------------------------------------

	virtual void onFrontConnected(){};

	virtual void onFrontDisconnected(int i){};

	virtual void onHeartBeatWarning(int i){};

	virtual void onRspAuthenticate(dict data, dict error, int id, bool last) {};

	virtual void onRspUserLogin(dict data, dict error, int id, bool last) {};

	virtual void onRspUserLogout(dict data, dict error, int id, bool last) {};

	virtual void onRspUserPasswordUpdate(dict data, dict error, int id, bool last) {};

	virtual void onRspTradingAccountPasswordUpdate(dict data, dict error, int id, bool last) {};

	virtual void onRspOrderInsert(dict data, dict error, int id, bool last) {};

	virtual void onRspParkedOrderInsert(dict data, dict error, int id, bool last) {};

	virtual void onRspParkedOrderAction(dict data, dict error, int id, bool last) {};

	virtual void onRspOrderAction(dict data, dict error, int id, bool last) {};

	virtual void onRspQueryMaxOrderVolume(dict data, dict error, int id, bool last) {};

	virtual void onRspSettlementInfoConfirm(dict data, dict error, int id, bool last) {};

	virtual void onRspRemoveParkedOrder(dict data, dict error, int id, bool last) {};

	virtual void onRspRemoveParkedOrderAction(dict data, dict error, int id, bool last) {};

	virtual void onRspExecOrderInsert(dict data, dict error, int id, bool last) {};

	virtual void onRspExecOrderAction(dict data, dict error, int id, bool last) {};

	virtual void onRspForQuoteInsert(dict data, dict error, int id, bool last) {};

	virtual void onRspQuoteInsert(dict data, dict error, int id, bool last) {};

	virtual void onRspQuoteAction(dict data, dict error, int id, bool last) {};

	virtual void onRspBatchOrderAction(dict data, dict error, int id, bool last) {};

	virtual void onRspOptionSelfCloseInsert(dict data, dict error, int id, bool last) {};

	virtual void onRspOptionSelfCloseAction(dict data, dict error, int id, bool last) {};

	virtual void onRspTransFund(dict data, dict error, int id, bool last) {};

	virtual void onRspQryOrder(dict data, dict error, int id, bool last) {};

	virtual void onRspQryTrade(dict data, dict error, int id, bool last) {};

	virtual void onRspQryInvestorPosition(dict data, dict error, int id, bool last) {};

	virtual void onRspQryTradingAccount(dict data, dict error, int id, bool last) {};

	virtual void onRspQryInvestor(dict data, dict error, int id, bool last) {};

	virtual void onRspQryTradingCode(dict data, dict error, int id, bool last) {};

	virtual void onRspQryInstrumentMarginRate(dict data, dict error, int id, bool last) {};

	virtual void onRspQryInstrumentCommissionRate(dict data, dict error, int id, bool last) {};

	virtual void onRspQryExchange(dict data, dict error, int id, bool last) {};

	virtual void onRspQryProduct(dict data, dict error, int id, bool last) {};

	virtual void onRspQryInstrument(dict data, dict error, int id, bool last) {};

	virtual void onRspQryDepthMarketData(dict data, dict error, int id, bool last) {};

	virtual void onRspQrySettlementInfo(dict data, dict error, int id, bool last) {};

	virtual void onRspQryInstrumentStatus(dict data, dict error, int id, bool last) {};

	virtual void onRspQryTransferBank(dict data, dict error, int id, bool last) {};

	virtual void onRspQryInvestorPositionDetail(dict data, dict error, int id, bool last) {};

	virtual void onRspQryNotice(dict data, dict error, int id, bool last) {};

	virtual void onRspQrySettlementInfoConfirm(dict data, dict error, int id, bool last) {};

	virtual void onRspQryInvestorPositionCombineDetail(dict data, dict error, int id, bool last) {};

	virtual void onRspQryCFMMCTradingAccountKey(dict data, dict error, int id, bool last) {};

	virtual void onRspQryEWarrantOffset(dict data, dict error, int id, bool last) {};

	virtual void onRspQryInvestorProductGroupMargin(dict data, dict error, int id, bool last) {};

	virtual void onRspQryExchangeMarginRate(dict data, dict error, int id, bool last) {};

	virtual void onRspQryExchangeMarginRateAdjust(dict data, dict error, int id, bool last) {};

	virtual void onRspQryExchangeRate(dict data, dict error, int id, bool last) {};

	virtual void onRspQrySecAgentACIDMap(dict data, dict error, int id, bool last) {};

	virtual void onRspQryOptionInstrTradeCost(dict data, dict error, int id, bool last) {};

	virtual void onRspQryOptionInstrCommRate(dict data, dict error, int id, bool last) {};

	virtual void onRspQryExecOrder(dict data, dict error, int id, bool last) {};

	virtual void onRspQryForQuote(dict data, dict error, int id, bool last) {};

	virtual void onRspQryQuote(dict data, dict error, int id, bool last) {};

	virtual void onRspQryOptionSelfClose(dict data, dict error, int id, bool last) {};

	virtual void onRspQryTransferSerial(dict data, dict error, int id, bool last) {};

	virtual void onRspQryAccountregister(dict data, dict error, int id, bool last) {};

	virtual void onRspError(dict error, int id, bool last) {};

	virtual void onRtnOrder(dict data) {};

	virtual void onRtnTrade(dict data) {};

	virtual void onErrRtnOrderInsert(dict data, dict error) {};

	virtual void onErrRtnOrderAction(dict data, dict error) {};

	virtual void onRtnInstrumentStatus(dict data) {};

	virtual void onRtnTradingNotice(dict data) {};

	virtual void onRtnErrorConditionalOrder(dict data) {};

	virtual void onRtnExecOrder(dict data) {};

	virtual void onErrRtnExecOrderInsert(dict data, dict error) {};

	virtual void onErrRtnExecOrderAction(dict data, dict error) {};

	virtual void onErrRtnForQuoteInsert(dict data, dict error) {};

	virtual void onRtnQuote(dict data) {};

	virtual void onErrRtnQuoteInsert(dict data, dict error) {};

	virtual void onErrRtnQuoteAction(dict data, dict error) {};

	virtual void onRtnForQuoteRsp(dict data) {};

	virtual void onErrRtnBatchOrderAction(dict data, dict error) {};

	virtual void onRtnOptionSelfClose(dict data) {};

	virtual void onErrRtnOptionSelfCloseInsert(dict data, dict error) {};

	virtual void onErrRtnOptionSelfCloseAction(dict data, dict error) {};

	virtual void onRspQryContractBank(dict data, dict error, int id, bool last) {};

	virtual void onRspQryParkedOrder(dict data, dict error, int id, bool last) {};

	virtual void onRspQryParkedOrderAction(dict data, dict error, int id, bool last) {};

	virtual void onRspQryTradingNotice(dict data, dict error, int id, bool last) {};

	virtual void onRspQryBrokerTradingParams(dict data, dict error, int id, bool last) {};

	virtual void onRspQryBrokerTradingAlgos(dict data, dict error, int id, bool last) {};

	virtual void onRtnFromBankToFutureByBank(dict data) {};

	virtual void onRtnFromFutureToBankByBank(dict data) {};

	virtual void onRtnRepealFromBankToFutureByBank(dict data) {};

	virtual void onRtnRepealFromFutureToBankByBank(dict data) {};

	virtual void onRtnFromBankToFutureByFuture(dict data) {};

	virtual void onRtnFromFutureToBankByFuture(dict data) {};

	virtual void onRtnRepealFromBankToFutureByFutureManual(dict data) {};

	virtual void onRtnRepealFromFutureToBankByFutureManual(dict data) {};

	virtual void onRtnQueryBankBalanceByFuture(dict data) {};

	virtual void onErrRtnBankToFutureByFuture(dict data, dict error) {};

	virtual void onErrRtnFutureToBankByFuture(dict data, dict error) {};

	virtual void onErrRtnRepealBankToFutureByFutureManual(dict data, dict error) {};

	virtual void onErrRtnRepealFutureToBankByFutureManual(dict data, dict error) {};

	virtual void onErrRtnQueryBankBalanceByFuture(dict data, dict error) {};

	virtual void onRtnRepealFromBankToFutureByFuture(dict data) {};

	virtual void onRtnRepealFromFutureToBankByFuture(dict data) {};

	virtual void onRspFromBankToFutureByFuture(dict data, dict error, int id, bool last) {};

	virtual void onRspFromFutureToBankByFuture(dict data, dict error, int id, bool last) {};

	virtual void onRspQueryBankAccountMoneyByFuture(dict data, dict error, int id, bool last) {};

	virtual void onRtnOpenAccountByBank(dict data) {};

	virtual void onRtnCancelAccountByBank(dict data) {};

	virtual void onRtnChangeAccountByBank(dict data) {};

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

	int reqAuthenticate(dict req, int nRequestID);

	int reqUserLogin(dict req, int nRequestID);

	int reqUserLoginEncrypt(dict req, int nRequestID);

	int reqUserLogout(dict req, int nRequestID);

	int reqUserPasswordUpdate(dict req, int nRequestID);

	int reqTradingAccountPasswordUpdate(dict req, int nRequestID);

	int reqOrderInsert(dict req, int nRequestID);

	int reqParkedOrderInsert(dict req, int nRequestID);

	int reqParkedOrderAction(dict req, int nRequestID);

	int reqOrderAction(dict req, int nRequestID);

	int reqQueryMaxOrderVolume(dict req, int nRequestID);

	int reqSettlementInfoConfirm(dict req, int nRequestID);

	int reqRemoveParkedOrder(dict req, int nRequestID);

	int reqRemoveParkedOrderAction(dict req, int nRequestID);

	int reqExecOrderInsert(dict req, int nRequestID);

	int reqExecOrderAction(dict req, int nRequestID);

	int reqForQuoteInsert(dict req, int nRequestID);

	int reqQuoteInsert(dict req, int nRequestID);

	int reqQuoteAction(dict req, int nRequestID);

	int reqBatchOrderAction(dict req, int nRequestID);

	int reqOptionSelfCloseInsert(dict req, int nRequestID);

	int reqOptionSelfCloseAction(dict req, int nRequestID);

	int reqTransFund(dict req, int nRequestID);

	int reqQryOrder(dict req, int nRequestID);

	int reqQryTrade(dict req, int nRequestID);

	int reqQryInvestorPosition(dict req, int nRequestID);

	int reqQryTradingAccount(dict req, int nRequestID);

	int reqQryInvestor(dict req, int nRequestID);

	int reqQryTradingCode(dict req, int nRequestID);

	int reqQryInstrumentMarginRate(dict req, int nRequestID);

	int reqQryInstrumentCommissionRate(dict req, int nRequestID);

	int reqQryExchange(dict req, int nRequestID);

	int reqQryProduct(dict req, int nRequestID);

	int reqQryInstrument(dict req, int nRequestID);

	int reqQryDepthMarketData(dict req, int nRequestID);

	int reqQryOptionSelfClose(dict req, int nRequestID);

	int reqQrySettlementInfo(dict req, int nRequestID);

	int reqQryInstrumentStatus(dict req, int nRequestID);

	int reqQryTransferBank(dict req, int nRequestID);

	int reqQryInvestorPositionDetail(dict req, int nRequestID);

	int reqQryNotice(dict req, int nRequestID);

	int reqQrySettlementInfoConfirm(dict req, int nRequestID);

	int reqQryInvestorPositionCombineDetail(dict req, int nRequestID);

	int reqQryCFMMCTradingAccountKey(dict req, int nRequestID);

	int reqQryEWarrantOffset(dict req, int nRequestID);

	int reqQryInvestorProductGroupMargin(dict req, int nRequestID);

	int reqQryExchangeMarginRate(dict req, int nRequestID);

	int reqQryExchangeMarginRateAdjust(dict req, int nRequestID);

	int reqQryExchangeRate(dict req, int nRequestID);

	int reqQrySecAgentACIDMap(dict req, int nRequestID);

	int reqQryOptionInstrTradeCost(dict req, int nRequestID);

	int reqQryOptionInstrCommRate(dict req, int nRequestID);

	int reqQryExecOrder(dict req, int nRequestID);

	int reqQryForQuote(dict req, int nRequestID);

	int reqQryQuote(dict req, int nRequestID);

	int reqQryTransferSerial(dict req, int nRequestID);

	int reqQryAccountregister(dict req, int nRequestID);

	int reqQryContractBank(dict req, int nRequestID);

	int reqQryParkedOrder(dict req, int nRequestID);

	int reqQryParkedOrderAction(dict req, int nRequestID);

	int reqQryTradingNotice(dict req, int nRequestID);

	int reqQryBrokerTradingParams(dict req, int nRequestID);

	int reqQryBrokerTradingAlgos(dict req, int nRequestID);

	int reqFromBankToFutureByFuture(dict req, int nRequestID);

	int reqFromFutureToBankByFuture(dict req, int nRequestID);

	int reqQueryBankAccountMoneyByFuture(dict req, int nRequestID);
};

