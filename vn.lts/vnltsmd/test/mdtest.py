# encoding = UTF-8

import sys
from time import sleep

from PyQt4 import QtGui

from vnltsmd import *


#----------------------------------------------------------------------
def print_dict(d):
    """���ռ�ֵ��ӡһ���ֵ�"""
    for key,value in d.items():
        print key + ':' + str(value)
        
        
#----------------------------------------------------------------------
def simple_log(func):
    """��װ�����������������"""
    def wrapper(*args, **kw):
        print ""
        print str(func.__name__)
        return func(*args, **kw)
    return wrapper


########################################################################
class TestMdApi(MdApi):
    """������ʵ��"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        super(TestMdApi, self).__init__()
        
    #----------------------------------------------------------------------
    @simple_log    
    def onFrontConnected(self):
        """����������"""
        pass
    
    #----------------------------------------------------------------------
    @simple_log    
    def onFrontDisconnected(self, n):
        """�������Ͽ�"""
        print n
        
    #----------------------------------------------------------------------
    @simple_log    
    def onHeartBeatWarning(self, n):
        """��������"""
        print n
    
    #----------------------------------------------------------------------
    @simple_log    
    def onRspError(self, error, n, last):
        """����"""
        print_dict(error)
    
    #----------------------------------------------------------------------
    def onRspUserLogin(self, data, error, n, last):
        """��½�ر�"""
        print_dict(data)
        print_dict(error)
        
    #----------------------------------------------------------------------
    @simple_log    
    def onRspUserLogout(self, data, error, n, last):
        """�ǳ��ر�"""
        print_dict(data)
        print_dict(error)
        
    #----------------------------------------------------------------------
    @simple_log    
    def onRspSubMarketData(self, data, error, n, last):
        """���ĺ�Լ�ر�"""
        print_dict(data)
        print_dict(error)
        
    #----------------------------------------------------------------------
    @simple_log    
    def onRspUnSubMarketData(self, data, error, n, last):
        """�˶���Լ�ر�"""
        print_dict(data)
        print_dict(error)    
        
    #----------------------------------------------------------------------
    @simple_log    
    def onRtnDepthMarketData(self, data):
        """��������"""
        print_dict(data)
        


#----------------------------------------------------------------------
def main():
    """�����Ժ��������ֶ���ʱ���Կ���ʹ��sleep"""
    reqid = 0
    
    # ����QtӦ�ö��������¼�ѭ��
    app = QtGui.QApplication(sys.argv)

    # ����API����
    api = TestMdApi()
    
    # ��C++�����д���MdApi���󣬴��������ϣ����������.con�ļ��ĵ�ַ
    api.createFtdcMdApi('')
    
    # ע��ǰ�û���ַ
    api.registerFront("tcp://101.231.210.1:24513")
    
    # ��ʼ��api������ǰ�û�
    api.init()
    sleep(0.5)
    
    # ��½
    loginReq = {}                           # ����һ�����ֵ�
    loginReq['UserID'] = ''                 # ������Ϊ�ֵ��ֵ�ķ�ʽ����
    loginReq['Password'] = ''               # ������C++�еĽṹ���Ա����Ӧ
    loginReq['BrokerID'] = '2011'    
    reqid = reqid + 1                       # ���������뱣��Ψһ��
    i = api.reqUserLogin(loginReq, 1)
    sleep(0.5)
    
    ## �ǳ�
    #reqid = reqid + 1
    #i = api.reqUserLogout({}, 1)
    #sleep(0.5)
    
    # ��ȡ�����գ�Ŀǰ���Ϊ��
    #day = api.getTradingDay()
    #print 'Trading Day is:' + str(day)
    #sleep(0.5)
    
    # ���ĺ�Լ
    subReq = {}
    subReq['InstrumentID'] = '600600'
    subReq['ExchangeID'] = 'SSE'
    i = api.subscribeMarketData(subReq)
    
    ## �˶���Լ
    #i = api.unSubscribeMarketData(subReq)
    
    # �������У������������
    app.exec_()
    
    
    
if __name__ == '__main__':
    main()
