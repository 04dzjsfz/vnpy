// vnctpmd.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "vnoesmd.h"


///-------------------------------------------------------------------------------------
///C++�Ļص����������ݱ��浽������
///-------------------------------------------------------------------------------------
int32 MdApi::OnConnected(eMdsApiChannelTypeT channelType, MdsApiSessionInfoT *pSessionInfo, MdsApiSubscribeInfoT *pSubscribeInfo)
{
	Task task = Task();
	task.task_name = ONCONNECTED;
	task.task_int = channelType;

	if (pSessionInfo)
	{
		MdsApiSessionInfoT *task_data = new MdsApiSessionInfoT();
		*task_data = *pSessionInfo;
		task.task_data = task_data;
	}
	this->task_queue.push(task);

	return EAGAIN;

};

int32 MdApi::OnDisconnected(eMdsApiChannelTypeT channelType, MdsApiSessionInfoT *pSessionInfo)
{
	Task task = Task();
	task.task_name = ONDISCONNECTED;
	task.task_int = channelType;

	if (pSessionInfo)
	{
		MdsApiSessionInfoT *task_data = new MdsApiSessionInfoT();
		*task_data = *pSessionInfo;
		task.task_data = task_data;
	}
	this->task_queue.push(task);

	return EAGAIN;
};



///-------------------------------------------------------------------------------------
///�����̴߳Ӷ�����ȡ�����ݣ�ת��Ϊpython����󣬽�������
///-------------------------------------------------------------------------------------

void MdApi::processTask()
{
	try
	{
		while (this->active)
		{
			Task task = this->task_queue.pop();

			switch (task.task_name)
			{
			case ONCONNECTED:
			{
				this->processConnected(&task);
				break;
			}

			case ONDISCONNECTED:
			{
				this->processDisconnected(&task);
				break;
			}


			};
		}
	}
	catch (const TerminatedError&)
	{
	}
};

int32 MdApi::processConnected(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		MdsApiSessionInfoT *task_data = (MdsApiSessionInfoT*)task->task_data;
		data["remoteHostNum"] = task_data->remoteHostNum;
		delete task_data;
	}
	this->onConnected(task->task_int, data);
};

int32 MdApi::processDisconnected(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		MdsApiSessionInfoT *task_data = (MdsApiSessionInfoT*)task->task_data;
		data["remoteHostNum"] = task_data->remoteHostNum;
		delete task_data;
	}
	this->onDisconnected(task->task_int, data);
};



///-------------------------------------------------------------------------------------
///��������
///-------------------------------------------------------------------------------------
void MdApi::createMdApi()
{
	this->api = new MdsClientApi();
	this->api->RegisterSpi(this);
}


bool MdApi::loadCfg(string pCfgFile)
{
	bool i = this->api->LoadCfg((char*)pCfgFile.c_str());
	return i;
}


bool MdApi::setCustomizedIp(string pIpStr)
{
	bool i = this->api->SetCustomizedIp((char*)pIpStr.c_str());
	return i;
}

bool MdApi::setCustomizedMac(string pMacStr)
{
	bool  i = this->api->SetCustomizedMac((char*)pMacStr.c_str());
	return i;
}

bool MdApi::setCustomizedDriverId(string pDriverStr)
{
	bool  i = this->api->SetCustomizedDriverId((char*)pDriverStr.c_str());
	return i;
}

void MdApi::setThreadUsername(string pUsername)
{
	this->api->SetThreadUsername((char*)pUsername.c_str());
}


void MdApi::setThreadPassword(string pPassword)
{
	this->api->SetThreadPassword((char*)pPassword.c_str());
}


bool MdApi::init()
{
	this->active = true;
	this->task_thread = thread(&MdApi::processTask, this);
	int32 LastClSeqNo;
	bool i = this->api->Start(&LastClSeqNo, 0);
	return i;
}

int MdApi::exit()
{
	this->active = false;
	this->task_queue.terminate();
	this->task_thread.join();

	this->api->RegisterSpi(NULL);
	this->api->Stop();
	this->api = NULL;
	return 1;
};



///-------------------------------------------------------------------------------------
///Boost.Python��װ
///-------------------------------------------------------------------------------------

class PyMdApi : public MdApi
{
public:
	using MdApi::MdApi;

	void onConnected(int channelType, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onConnected, channelType, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onDisconnected(int channelType, const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onDisconnected, channelType, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};



};


PYBIND11_MODULE(vnoesmd, m)
{
	class_<MdApi, PyMdApi> MdApi(m, "MdApi", module_local());
	MdApi
		.def(init<>())
		.def("createMdApi", &MdApi::createMdApi)
		.def("loadCfg", &MdApi::loadCfg)
		.def("setCustomizedIp", &MdApi::setCustomizedIp)
		.def("setCustomizedMac", &MdApi::setCustomizedMac)
		.def("setCustomizedDriverId", &MdApi::setCustomizedDriverId)
		.def("setThreadUsername", &MdApi::setThreadUsername)
		.def("setThreadPassword", &MdApi::setThreadPassword)
		.def("init", &MdApi::init)
		.def("exit", &MdApi::exit)

		.def("onConnected", &MdApi::onConnected)
		.def("onDisconnected", &MdApi::onDisconnected)
		;

}
