﻿// vnxtpmd.cpp : 定义 DLL 应用程序的导出函数。
//

#include "vnxtpmd.h"


///-------------------------------------------------------------------------------------
///C++的回调函数将数据保存到队列中
///-------------------------------------------------------------------------------------

void MdApi::OnDisconnected(int reason)
{
	Task task = Task();
	task.task_name = ONDISCONNECTED;
	task.task_int = reason;
	this->task_queue.push(task);
};

void MdApi::OnError(XTPRI *error_info)
{
	Task task = Task();
	task.task_name = ONERROR;
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void MdApi::OnSubMarketData(XTPST *ticker, XTPRI *error_info, bool is_last)
{
	Task task = Task();
	task.task_name = ONSUBMARKETDATA;
	if (ticker)
	{
		XTPST *task_data = new XTPST();
		*task_data = *ticker;
		task.task_data = task_data;
	}
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	task.task_last = is_last;
	this->task_queue.push(task);
};

void MdApi::OnUnSubMarketData(XTPST *ticker, XTPRI *error_info, bool is_last)
{
	Task task = Task();
	task.task_name = ONUNSUBMARKETDATA;
	if (ticker)
	{
		XTPST *task_data = new XTPST();
		*task_data = *ticker;
		task.task_data = task_data;
	}
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	task.task_last = is_last;
	this->task_queue.push(task);
};

void MdApi::OnDepthMarketData(XTPMD *market_data, int bid1_qty int bid1_count, int max_bid1_count, int ask1_qty int ask1_count, int max_ask1_count)
{
	Task task = Task();
	task.task_name = ONDEPTHMARKETDATA;
	if (market_data)
	{
		XTPMD *task_data = new XTPMD();
		*task_data = *market_data;
		task.task_data = task_data;
	}
	task.task_int = bid1_qty;
	task.task_int = bid1_count;
	task.task_int = max_bid1_count;
	task.task_int = ask1_qty;
	task.task_int = ask1_count;
	task.task_int = max_ask1_count;
	this->task_queue.push(task);
};

void MdApi::OnSubOrderBook(XTPST *ticker, XTPRI *error_info, bool is_last)
{
	Task task = Task();
	task.task_name = ONSUBORDERBOOK;
	if (ticker)
	{
		XTPST *task_data = new XTPST();
		*task_data = *ticker;
		task.task_data = task_data;
	}
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	task.task_last = is_last;
	this->task_queue.push(task);
};

void MdApi::OnUnSubOrderBook(XTPST *ticker, XTPRI *error_info, bool is_last)
{
	Task task = Task();
	task.task_name = ONUNSUBORDERBOOK;
	if (ticker)
	{
		XTPST *task_data = new XTPST();
		*task_data = *ticker;
		task.task_data = task_data;
	}
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	task.task_last = is_last;
	this->task_queue.push(task);
};

void MdApi::OnOrderBook(XTPOB *order_book)
{
	Task task = Task();
	task.task_name = ONORDERBOOK;
	if (order_book)
	{
		XTPOB *task_data = new XTPOB();
		*task_data = *order_book;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void MdApi::OnSubTickByTick(XTPST *ticker, XTPRI *error_info, bool is_last)
{
	Task task = Task();
	task.task_name = ONSUBTICKBYTICK;
	if (ticker)
	{
		XTPST *task_data = new XTPST();
		*task_data = *ticker;
		task.task_data = task_data;
	}
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	task.task_last = is_last;
	this->task_queue.push(task);
};

void MdApi::OnUnSubTickByTick(XTPST *ticker, XTPRI *error_info, bool is_last)
{
	Task task = Task();
	task.task_name = ONUNSUBTICKBYTICK;
	if (ticker)
	{
		XTPST *task_data = new XTPST();
		*task_data = *ticker;
		task.task_data = task_data;
	}
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	task.task_last = is_last;
	this->task_queue.push(task);
};

void MdApi::OnTickByTick(XTPTBT *tbt_data)
{
	Task task = Task();
	task.task_name = ONTICKBYTICK;
	if (tbt_data)
	{
		XTPTBT *task_data = new XTPTBT();
		*task_data = *tbt_data;
		task.task_data = task_data;
	}
	this->task_queue.push(task);
};

void MdApi::OnSubscribeAllMarketData(int exchange_id, XTPRI *error_info)
{
	Task task = Task();
	task.task_name = ONSUBSCRIBEALLMARKETDATA;
	task.task_int = (int)exchange_id;
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void MdApi::OnUnSubscribeAllMarketData(int exchange_id, XTPRI *error_info)
{
	Task task = Task();
	task.task_name = ONUNSUBSCRIBEALLMARKETDATA;
	task.task_int = (int)exchange_id;
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void MdApi::OnSubscribeAllOrderBook(int exchange_id, XTPRI *error_info)
{
	Task task = Task();
	task.task_name = ONSUBSCRIBEALLORDERBOOK;
	task.task_int = (int)exchange_id;
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void MdApi::OnUnSubscribeAllOrderBook(int exchange_id, XTPRI *error_info)
{
	Task task = Task();
	task.task_name = ONUNSUBSCRIBEALLORDERBOOK;
	task.task_int = (int)exchange_id;
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void MdApi::OnSubscribeAllTickByTick(int exchange_id, XTPRI *error_info)
{
	Task task = Task();
	task.task_name = ONSUBSCRIBEALLTICKBYTICK;
	task.task_int = (int)exchange_id;
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void MdApi::OnUnSubscribeAllTickByTick(int exchange_id, XTPRI *error_info)
{
	Task task = Task();
	task.task_name = ONUNSUBSCRIBEALLTICKBYTICK;
	task.task_int = (int)exchange_id;
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void MdApi::OnQueryAllTickers(XTPQSI* ticker_info, XTPRI *error_info, bool is_last)
{
	Task task = Task();
	task.task_name = ONQUERYALLTICKERS;
	if (ticker_info)
	{
		XTPQSI *task_data = new XTPQSI();
		*task_data = *ticker_info;
		task.task_data = task_data;
	}
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	task.task_last = is_last;
	this->task_queue.push(task);
};

void MdApi::OnQueryTickersPriceInfo(XTPTPI* ticker_info, XTPRI *error_info, bool is_last)
{
	Task task = Task();
	task.task_name = ONQUERYTICKERSPRICEINFO;
	if (ticker_info)
	{
		XTPTPI *task_data = new XTPTPI();
		*task_data = *ticker_info;
		task.task_data = task_data;
	}
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	task.task_last = is_last;
	this->task_queue.push(task);
};

void MdApi::OnSubscribeAllOptionMarketData(int exchange_id, XTPRI *error_info)
{
	Task task = Task();
	task.task_name = ONSUBSCRIBEALLOPTIONMARKETDATA;
	task.task_int = (int)exchange_id;
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void MdApi::OnUnSubscribeAllOptionMarketData(int exchange_id, XTPRI *error_info)
{
	Task task = Task();
	task.task_name = ONUNSUBSCRIBEALLOPTIONMARKETDATA;
	task.task_int = (int)exchange_id;
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void MdApi::OnSubscribeAllOptionOrderBook(int exchange_id, XTPRI *error_info)
{
	Task task = Task();
	task.task_name = ONSUBSCRIBEALLOPTIONORDERBOOK;
	task.task_int = (int)exchange_id;
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void MdApi::OnUnSubscribeAllOptionOrderBook(int exchange_id, XTPRI *error_info)
{
	Task task = Task();
	task.task_name = ONUNSUBSCRIBEALLOPTIONORDERBOOK;
	task.task_int = (int)exchange_id;
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void MdApi::OnSubscribeAllOptionTickByTick(int exchange_id, XTPRI *error_info)
{
	Task task = Task();
	task.task_name = ONSUBSCRIBEALLOPTIONTICKBYTICK;
	task.task_int = (int)exchange_id;
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};

void MdApi::OnUnSubscribeAllOptionTickByTick(int exchange_id, XTPRI *error_info)
{
	Task task = Task();
	task.task_name = ONUNSUBSCRIBEALLOPTIONTICKBYTICK;
	task.task_int = (int)exchange_id;
	if (error_info)
	{
		XTPRI *task_error = new XTPRI();
		*task_error = *error_info;
		task.task_error = task_error;
	}
	this->task_queue.push(task);
};





///-------------------------------------------------------------------------------------
///工作线程从队列中取出数据，转化为python对象后，进行推送
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
			case ONDISCONNECTED:
			{
				this->processDisconnected(&task);
				break;
			}

			case ONERROR:
			{
				this->processError(&task);
				break;
			}

			case ONSUBMARKETDATA:
			{
				this->processSubMarketData(&task);
				break;
			}

			case ONUNSUBMARKETDATA:
			{
				this->processUnSubMarketData(&task);
				break;
			}

			case ONDEPTHMARKETDATA:
			{
				this->processDepthMarketData(&task);
				break;
			}

			case ONSUBORDERBOOK:
			{
				this->processSubOrderBook(&task);
				break;
			}

			case ONUNSUBORDERBOOK:
			{
				this->processUnSubOrderBook(&task);
				break;
			}

			case ONORDERBOOK:
			{
				this->processOrderBook(&task);
				break;
			}

			case ONSUBTICKBYTICK:
			{
				this->processSubTickByTick(&task);
				break;
			}

			case ONUNSUBTICKBYTICK:
			{
				this->processUnSubTickByTick(&task);
				break;
			}

			case ONTICKBYTICK:
			{
				this->processTickByTick(&task);
				break;
			}

			case ONSUBSCRIBEALLMARKETDATA:
			{
				this->processSubscribeAllMarketData(&task);
				break;
			}

			case ONUNSUBSCRIBEALLMARKETDATA:
			{
				this->processUnSubscribeAllMarketData(&task);
				break;
			}

			case ONSUBSCRIBEALLORDERBOOK:
			{
				this->processSubscribeAllOrderBook(&task);
				break;
			}

			case ONUNSUBSCRIBEALLORDERBOOK:
			{
				this->processUnSubscribeAllOrderBook(&task);
				break;
			}

			case ONSUBSCRIBEALLTICKBYTICK:
			{
				this->processSubscribeAllTickByTick(&task);
				break;
			}

			case ONUNSUBSCRIBEALLTICKBYTICK:
			{
				this->processUnSubscribeAllTickByTick(&task);
				break;
			}

			case ONQUERYALLTICKERS:
			{
				this->processQueryAllTickers(&task);
				break;
			}

			case ONQUERYTICKERSPRICEINFO:
			{
				this->processQueryTickersPriceInfo(&task);
				break;
			}

			case ONSUBSCRIBEALLOPTIONMARKETDATA:
			{
				this->processSubscribeAllOptionMarketData(&task);
				break;
			}

			case ONUNSUBSCRIBEALLOPTIONMARKETDATA:
			{
				this->processUnSubscribeAllOptionMarketData(&task);
				break;
			}

			case ONSUBSCRIBEALLOPTIONORDERBOOK:
			{
				this->processSubscribeAllOptionOrderBook(&task);
				break;
			}

			case ONUNSUBSCRIBEALLOPTIONORDERBOOK:
			{
				this->processUnSubscribeAllOptionOrderBook(&task);
				break;
			}

			case ONSUBSCRIBEALLOPTIONTICKBYTICK:
			{
				this->processSubscribeAllOptionTickByTick(&task);
				break;
			}

			case ONUNSUBSCRIBEALLOPTIONTICKBYTICK:
			{
				this->processUnSubscribeAllOptionTickByTick(&task);
				break;
			}
			};
		}
	}
	catch (const TerminatedError&)
	{
	}
};

void MdApi::processDisconnected(Task *task)
{
	gil_scoped_acquire acquire;
	this->onDisconnected(task->task_int);
};

void MdApi::processError(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onError(error);
};

void MdApi::processSubMarketData(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPST *task_data = (XTPST*)task->task_data;
		data["exchange_id"] = task_data->exchange_id;
		data["ticker"] = toUtf(task_data->ticker);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onSubMarketData(data, error, task->task_last);
};

void MdApi::processUnSubMarketData(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPST *task_data = (XTPST*)task->task_data;
		data["exchange_id"] = task_data->exchange_id;
		data["ticker"] = toUtf(task_data->ticker);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onUnSubMarketData(data, error, task->task_last);
};

void MdApi::processDepthMarketData(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPMD *task_data = (XTPMD*)task->task_data;
		data["exchange_id"] = task_data->exchange_id;
		data["ticker"] = toUtf(task_data->ticker);
		data["last_price"] = task_data->last_price;
		data["pre_close_price"] = task_data->pre_close_price;
		data["open_price"] = task_data->open_price;
		data["high_price"] = task_data->high_price;
		data["low_price"] = task_data->low_price;
		data["close_price"] = task_data->close_price;
		data["pre_total_long_positon"] = task_data->pre_total_long_positon;
		data["total_long_positon"] = task_data->total_long_positon;
		data["pre_settl_price"] = task_data->pre_settl_price;
		data["settl_price"] = task_data->settl_price;
		data["upper_limit_price"] = task_data->upper_limit_price;
		data["lower_limit_price"] = task_data->lower_limit_price;
		data["pre_delta"] = task_data->pre_delta;
		data["curr_delta"] = task_data->curr_delta;
		data["data_time"] = task_data->data_time;
		data["qty"] = task_data->qty;
		data["turnover"] = task_data->turnover;
		data["avg_price"] = task_data->avg_price;
		data["bid"] = task_data->bid;
		data["ask"] = task_data->ask;
		data["bid_qty"] = task_data->bid_qty;
		data["ask_qty"] = task_data->ask_qty;
		data["trades_count"] = task_data->trades_count;
		data["ticker_status"] = toUtf(task_data->ticker_status);
		data["data_type"] = task_data->data_type;
		data["r4"] = task_data->r4;
		delete task_data;
	}
	this->onDepthMarketData(data, task->task_int, task->task_int, task->task_int, task->task_int, task->task_int, task->task_int);
};

void MdApi::processSubOrderBook(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPST *task_data = (XTPST*)task->task_data;
		data["exchange_id"] = task_data->exchange_id;
		data["ticker"] = toUtf(task_data->ticker);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onSubOrderBook(data, error, task->task_last);
};

void MdApi::processUnSubOrderBook(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPST *task_data = (XTPST*)task->task_data;
		data["exchange_id"] = task_data->exchange_id;
		data["ticker"] = toUtf(task_data->ticker);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onUnSubOrderBook(data, error, task->task_last);
};

void MdApi::processOrderBook(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPOB *task_data = (XTPOB*)task->task_data;
		data["exchange_id"] = task_data->exchange_id;
		data["ticker"] = toUtf(task_data->ticker);
		data["last_price"] = task_data->last_price;
		data["qty"] = task_data->qty;
		data["turnover"] = task_data->turnover;
		data["trades_count"] = task_data->trades_count;
		data["bid"] = task_data->bid;
		data["ask"] = task_data->ask;
		data["bid_qty"] = task_data->bid_qty;
		data["ask_qty"] = task_data->ask_qty;
		data["data_time"] = task_data->data_time;
		delete task_data;
	}
	this->onOrderBook(data);
};

void MdApi::processSubTickByTick(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPST *task_data = (XTPST*)task->task_data;
		data["exchange_id"] = task_data->exchange_id;
		data["ticker"] = toUtf(task_data->ticker);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onSubTickByTick(data, error, task->task_last);
};

void MdApi::processUnSubTickByTick(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPST *task_data = (XTPST*)task->task_data;
		data["exchange_id"] = task_data->exchange_id;
		data["ticker"] = toUtf(task_data->ticker);
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onUnSubTickByTick(data, error, task->task_last);
};

void MdApi::processTickByTick(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPTBT *task_data = (XTPTBT*)task->task_data;
		data["exchange_id"] = task_data->exchange_id;
		data["ticker"] = toUtf(task_data->ticker);
		data["seq"] = task_data->seq;
		data["data_time"] = task_data->data_time;
		data["type"] = task_data->type;
		delete task_data;
	}
	this->onTickByTick(data);
};

void MdApi::processSubscribeAllMarketData(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onSubscribeAllMarketData(task->task_int, error);
};

void MdApi::processUnSubscribeAllMarketData(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onUnSubscribeAllMarketData(task->task_int, error);
};

void MdApi::processSubscribeAllOrderBook(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onSubscribeAllOrderBook(task->task_int, error);
};

void MdApi::processUnSubscribeAllOrderBook(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onUnSubscribeAllOrderBook(task->task_int, error);
};

void MdApi::processSubscribeAllTickByTick(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onSubscribeAllTickByTick(task->task_int, error);
};

void MdApi::processUnSubscribeAllTickByTick(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onUnSubscribeAllTickByTick(task->task_int, error);
};

void MdApi::processQueryAllTickers(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPQSI *task_data = (XTPQSI*)task->task_data;
		data["exchange_id"] = task_data->exchange_id;
		data["ticker"] = toUtf(task_data->ticker);
		data["ticker_name"] = toUtf(task_data->ticker_name);
		data["ticker_type"] = task_data->ticker_type;
		data["pre_close_price"] = task_data->pre_close_price;
		data["upper_limit_price"] = task_data->upper_limit_price;
		data["lower_limit_price"] = task_data->lower_limit_price;
		data["price_tick"] = task_data->price_tick;
		data["buy_qty_unit"] = task_data->buy_qty_unit;
		data["sell_qty_unit"] = task_data->sell_qty_unit;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onQueryAllTickers(data, error, task->task_last);
};

void MdApi::processQueryTickersPriceInfo(Task *task)
{
	gil_scoped_acquire acquire;
	dict data;
	if (task->task_data)
	{
		XTPTPI *task_data = (XTPTPI*)task->task_data;
		data["exchange_id"] = task_data->exchange_id;
		data["ticker"] = toUtf(task_data->ticker);
		data["last_price"] = task_data->last_price;
		delete task_data;
	}
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onQueryTickersPriceInfo(data, error, task->task_last);
};

void MdApi::processSubscribeAllOptionMarketData(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onSubscribeAllOptionMarketData(task->task_int, error);
};

void MdApi::processUnSubscribeAllOptionMarketData(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onUnSubscribeAllOptionMarketData(task->task_int, error);
};

void MdApi::processSubscribeAllOptionOrderBook(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onSubscribeAllOptionOrderBook(task->task_int, error);
};

void MdApi::processUnSubscribeAllOptionOrderBook(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onUnSubscribeAllOptionOrderBook(task->task_int, error);
};

void MdApi::processSubscribeAllOptionTickByTick(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onSubscribeAllOptionTickByTick(task->task_int, error);
};

void MdApi::processUnSubscribeAllOptionTickByTick(Task *task)
{
	gil_scoped_acquire acquire;
	dict error;
	if (task->task_error)
	{
		XTPRI *task_error = (XTPRI*)task->task_error;
		error["error_id"] = task_error->error_id;
		error["error_msg"] = toUtf(task_error->error_msg);
		delete task_error;
	}
	this->onUnSubscribeAllOptionTickByTick(task->task_int, error);
};





///-------------------------------------------------------------------------------------
///主动函数
///-------------------------------------------------------------------------------------

void MdApi::createFtdcMdApi(string pszFlowPath)
{
	this->api = CThostFtdcMdApi::CreateFtdcMdApi(pszFlowPath.c_str());
	this->api->RegisterSpi(this);
};

void MdApi::release()
{
	this->api->Release();
};

void MdApi::init()
{
	this->active = true;
	this->task_thread = thread(&MdApi::processTask, this);

	this->api->Init();
};

int MdApi::join()
{
	int i = this->api->Join();
	return i;
};

int MdApi::exit()
{
	this->active = false;
	this->task_queue.terminate();
	this->task_thread.join();

	this->api->RegisterSpi(NULL);
	this->api->Release();
	this->api = NULL;
	return 1;
};

string MdApi::getTradingDay()
{
	string day = this->api->GetTradingDay();
	return day;
};

void MdApi::registerFront(string pszFrontAddress)
{
	this->api->RegisterFront((char*)pszFrontAddress.c_str());
};

int MdApi::subscribeMarketData(string instrumentID)
{
	char* buffer = (char*)instrumentID.c_str();
	char* myreq[1] = { buffer };
	int i = this->api->SubscribeMarketData(myreq, 1);
	return i;
};

int MdApi::unSubscribeMarketData(string instrumentID)
{
	char* buffer = (char*)instrumentID.c_str();
	char* myreq[1] = { buffer };;
	int i = this->api->UnSubscribeMarketData(myreq, 1);
	return i;
};

int MdApi::subscribeForQuoteRsp(string instrumentID)
{
	char* buffer = (char*)instrumentID.c_str();
	char* myreq[1] = { buffer };
	int i = this->api->SubscribeForQuoteRsp(myreq, 1);
	return i;
};

int MdApi::unSubscribeForQuoteRsp(string instrumentID)
{
	char* buffer = (char*)instrumentID.c_str();
	char* myreq[1] = { buffer };;
	int i = this->api->UnSubscribeForQuoteRsp(myreq, 1);
	return i;
};

int MdApi::queryAllTickers(int exchange_id)
{
	XTP_EXCHANGE_TYPE myreq = XTP_EXCHANGE_TYPE();
	memset(&myreq, 0, sizeof(myreq));
	int i = this->api->QueryAllTickers(&myreq, (XTP_EXCHANGE_TYPE)exchange_id);
	return i;
};

int MdApi::queryTickersPriceInfo(char ticker, int count, int exchange_id)
{
	char myreq = char();
	memset(&myreq, 0, sizeof(myreq));
	int i = this->api->QueryTickersPriceInfo(&myreq, (XTP_EXCHANGE_TYPE) exchange_id);
	return i;
};

int MdApi::queryAllTickersPriceInfo()
{
	char myreq = char();
	memset(&myreq, 0, sizeof(myreq));
	int i = this->api->QueryAllTickersPriceInfo();
	return i;
};


///-------------------------------------------------------------------------------------
///Boost.Python封装
///-------------------------------------------------------------------------------------

class PyMdApi : public MdApi
{
public:
	using MdApi::MdApi;

	void onDisconnected(int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onDisconnected, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onError(const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onError, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onSubMarketData(const dict &data, const dict &error, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onSubMarketData, data, error, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onUnSubMarketData(const dict &data, const dict &error, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onUnSubMarketData, data, error, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onDepthMarketData(const dict &data, int reqid, int reqid, int reqid, int reqid, int reqid, int reqid) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onDepthMarketData, data, reqid, reqid, reqid, reqid, reqid, reqid);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onSubOrderBook(const dict &data, const dict &error, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onSubOrderBook, data, error, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onUnSubOrderBook(const dict &data, const dict &error, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onUnSubOrderBook, data, error, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onOrderBook(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onOrderBook, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onSubTickByTick(const dict &data, const dict &error, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onSubTickByTick, data, error, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onUnSubTickByTick(const dict &data, const dict &error, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onUnSubTickByTick, data, error, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onTickByTick(const dict &data) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onTickByTick, data);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onSubscribeAllMarketData(int data, const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onSubscribeAllMarketData, data, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onUnSubscribeAllMarketData(int data, const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onUnSubscribeAllMarketData, data, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onSubscribeAllOrderBook(int data, const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onSubscribeAllOrderBook, data, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onUnSubscribeAllOrderBook(int data, const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onUnSubscribeAllOrderBook, data, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onSubscribeAllTickByTick(int data, const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onSubscribeAllTickByTick, data, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onUnSubscribeAllTickByTick(int data, const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onUnSubscribeAllTickByTick, data, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryAllTickers(const dict &data, const dict &error, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onQueryAllTickers, data, error, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onQueryTickersPriceInfo(const dict &data, const dict &error, bool last) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onQueryTickersPriceInfo, data, error, last);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onSubscribeAllOptionMarketData(int data, const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onSubscribeAllOptionMarketData, data, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onUnSubscribeAllOptionMarketData(int data, const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onUnSubscribeAllOptionMarketData, data, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onSubscribeAllOptionOrderBook(int data, const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onSubscribeAllOptionOrderBook, data, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onUnSubscribeAllOptionOrderBook(int data, const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onUnSubscribeAllOptionOrderBook, data, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onSubscribeAllOptionTickByTick(int data, const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onSubscribeAllOptionTickByTick, data, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};

	void onUnSubscribeAllOptionTickByTick(int data, const dict &error) override
	{
		try
		{
			PYBIND11_OVERLOAD(void, MdApi, onUnSubscribeAllOptionTickByTick, data, error);
		}
		catch (const error_already_set &e)
		{
			cout << e.what() << endl;
		}
	};




};


PYBIND11_MODULE(vnctpmd, m)
{
	class_<MdApi, PyMdApi> mdapi(m, "MdApi", module_local());
	mdapi
		.def(init<>())
		.def("createFtdcMdApi", &MdApi::createFtdcMdApi)
		.def("release", &MdApi::release)
		.def("init", &MdApi::init)
		.def("join", &MdApi::join)
		.def("exit", &MdApi::exit)
		.def("getTradingDay", &MdApi::getTradingDay)
		.def("registerFront", &MdApi::registerFront)
		.def("subscribeMarketData", &MdApi::subscribeMarketData)
		.def("unSubscribeMarketData", &MdApi::unSubscribeMarketData)
		.def("subscribeForQuoteRsp", &MdApi::subscribeForQuoteRsp)
		.def("unSubscribeForQuoteRsp", &MdApi::unSubscribeForQuoteRsp)
		.def("queryAllTickers", &MdApi::queryAllTickers)
		.def("queryTickersPriceInfo", &MdApi::queryTickersPriceInfo)
		.def("queryAllTickersPriceInfo", &MdApi::queryAllTickersPriceInfo)

		.def("onDisconnected", &MdApi::onDisconnected)
		.def("onError", &MdApi::onError)
		.def("onSubMarketData", &MdApi::onSubMarketData)
		.def("onUnSubMarketData", &MdApi::onUnSubMarketData)
		.def("onDepthMarketData", &MdApi::onDepthMarketData)
		.def("onSubOrderBook", &MdApi::onSubOrderBook)
		.def("onUnSubOrderBook", &MdApi::onUnSubOrderBook)
		.def("onOrderBook", &MdApi::onOrderBook)
		.def("onSubTickByTick", &MdApi::onSubTickByTick)
		.def("onUnSubTickByTick", &MdApi::onUnSubTickByTick)
		.def("onTickByTick", &MdApi::onTickByTick)
		.def("onSubscribeAllMarketData", &MdApi::onSubscribeAllMarketData)
		.def("onUnSubscribeAllMarketData", &MdApi::onUnSubscribeAllMarketData)
		.def("onSubscribeAllOrderBook", &MdApi::onSubscribeAllOrderBook)
		.def("onUnSubscribeAllOrderBook", &MdApi::onUnSubscribeAllOrderBook)
		.def("onSubscribeAllTickByTick", &MdApi::onSubscribeAllTickByTick)
		.def("onUnSubscribeAllTickByTick", &MdApi::onUnSubscribeAllTickByTick)
		.def("onQueryAllTickers", &MdApi::onQueryAllTickers)
		.def("onQueryTickersPriceInfo", &MdApi::onQueryTickersPriceInfo)
		.def("onSubscribeAllOptionMarketData", &MdApi::onSubscribeAllOptionMarketData)
		.def("onUnSubscribeAllOptionMarketData", &MdApi::onUnSubscribeAllOptionMarketData)
		.def("onSubscribeAllOptionOrderBook", &MdApi::onSubscribeAllOptionOrderBook)
		.def("onUnSubscribeAllOptionOrderBook", &MdApi::onUnSubscribeAllOptionOrderBook)
		.def("onSubscribeAllOptionTickByTick", &MdApi::onSubscribeAllOptionTickByTick)
		.def("onUnSubscribeAllOptionTickByTick", &MdApi::onUnSubscribeAllOptionTickByTick)
		;

}



