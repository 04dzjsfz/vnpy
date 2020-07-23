
import time
import quickfix as fix
from datetime import datetime, timedelta
from vnpy.trader.utility import get_file_path, get_folder_path
from vnpy.trader.object import (
    OrderRequest,
)
import importlib
from vnpy.trader.constant import (
    Exchange,
    Product,
    Direction,
    OrderType,
    Status,
    Offset,
    OptionType
)

hours = timedelta(hours=1)
mins = timedelta(minutes=1)


EXCHANGE_VT2GNS = {
    Exchange.SSE: "SS",
    Exchange.SZSE: "SZ",
    Exchange.CFFEX: "CF",
    Exchange.SHFE: "SSC",
    Exchange.DCE: "DLC",
    Exchange.CZCE: "ZZC"
}

ORDERTYPE_VT2GNS = {
    OrderType.MARKET: "1",
    OrderType.LIMIT: "2"
}

DIRECTION_VT2GNS = {
    Direction.LONG: "1",
    Direction.SHORT: "2"
}


class FixClient(fix.Application):

    orderid: int = 100008
    execid: int = 0
    session_id = ""
    tradeid = 0
    mather_child_id = {}

    structs = {}

    # def __init__(self, orderid):
    #     self.orderid = orderid

    def load_struct(self):
        """加载Struct"""
        module_name = f"fix_dict"
        module = importlib.import_module(module_name)

        for name in dir(module):
            if "__" not in name:
                self.structs[name] = getattr(module, name)

        for k, v in self.structs.items():
            words = k.split("_")
            name = words[0]

    def onCreate(self, session_id):
        pass

    def onLogon(self, session_id):
        self.session_id = session_id
        if self.session_id:
            print("Session ID 获取成功， id=", self.session_id)

    def onLogout(self, session_id):
        print("4-onLogout")

    def toAdmin(self, msg, session_id):
        username = fix.Username("username")
        mypass = fix.Password("password")
        mycompid = fix.TargetSubID("targetsubid")
        msg.setField(username)
        msg.setField(mypass)
        msg.setField(mycompid)

    def fromAdmin(self, msg, session_id):
        d = self.msg2dict(msg)
        if d["<35>MsgType"] != "HEARTBEAT":
            print("@@Callback", d)

    def toApp(self, session_id, msg):
        d = self.msg2dict(msg)
        print("@@Sent the following msg: ", d)

    def fromApp(self, msg, session_id):
        d = self.msg2dict(msg)
        print("@@Received msg: ", d)

        msg_type = d["<35>MsgType"]
        if msg_type == "EXECUTION_REPORT":
            self.mather_child_id[d["<11>ClOrdID"]] = d["<37>OrderID"]

    def new_orderid(self) -> str:
        self.orderid = self.orderid + 1
        return str(self.orderid)

    def generate_execid(self):
        self.execid = self.execid + 1
        return self.execid

    def put_order(self, session_id, order):
        print("@@Creating Order----------------")
        fix.Session.sendToTarget(order, self.session_id)

    def generate_order(
        self,
        symbol,
        exchange,
        order_type,
        direction,
        volume=None,
        price=None,
    ):
        now_utc = datetime.utcnow()
        end_utc = now_utc + hours
        start_utc = now_utc - mins
        start_time = start_utc.strftime("%Y%m%d-%H:%M:%S")
        end_time = end_utc.strftime("%Y%m%d-%H:%M:%S")
        now_time = now_utc.strftime("%Y%m%d-%H:%M:%S")
        order = fix.Message()

        # Header
        order.getHeader().setField(fix.StringField(8, "FIX.4.2"))
        order.getHeader().setField(fix.MsgType(fix.MsgType_NewOrderSingle))  # MsgType

        order.getHeader().setField(fix.Account("account"))
        order.getHeader().setField(fix.TargetSubID("targetsubid"))

        # Body
        gns_exchange = EXCHANGE_VT2GNS[exchange]
        gns_symbol = f"{symbol}.{gns_exchange}"
        orderid = self.new_orderid()
        order.setField(11, orderid)
        order.setField(21, "2")
        order.setField(100, gns_exchange)
        order.setField(55, gns_symbol)

        if volume:
            order.setField(38, str(volume))
        else:
            order.setField(152, str(price))

        order.setField(40, ORDERTYPE_VT2GNS[order_type])
        if order_type == OrderType.LIMIT:
            order.setField(44, str(price))

        order.setField(15, "CNY")
        order.setField(60, now_time)
        order.setField(847, "TWAP")
        msg = f"StartTime;{start_time}^EndTime;{end_time}"
        order.setField(848, msg)
        order.setField(fix.CharField(54, fix.Side_BUY))

        return order

    def cancel_order(self):
        now_utc = datetime.utcnow()
        now_time = now_utc.strftime("%Y%m%d-%H:%M:%S")
        localid = str(self.orderid)
        new_localid = self.new_orderid()
        child_id = self.mather_child_id(localid)
        symbol = "600519"
        volume = 1000
        price = 0

        order = fix.Message()
        order.setField(35, "F")
        order.setField(11, localid)
        order.setField(41, new_localid)
        order.setField(37, child_id)
        order.setField(55, symbol)
        order.setField(fix.CharField(54, fix.Side_BUY))

        if volume:
            order.setField(38, str(volume))
        else:
            order.setField(152, str(price))
        order.setField(60, now_time)
        order.setField(847, "TWAP")
        self.put_order(self.session_id, order)

    def send_order(self, req: OrderRequest):
        order = self.generate_order(
            symbol=req.symbol,
            exchange=Exchange.SSE,
            volume=req.volume,
            order_type=OrderType.MARKET,
            direction=Direction.LONG
        )
        self.put_order(self.session_id, order)

    def msg2dict(self, msg) -> dict:
        d = {}
        msg_str = msg.toString()

        words = msg_str.split("\x01")
        words = [word for word in words if word != ""]
        if len(words) == 1 and words[0] == 'FIX.4.2:client06->GenusStgyUAT1':
            return

        for word in words:
            k, v = word.split("=")
            number = f"no_{k}"
            field = self.structs.get(number, None)
            if not field:
                field = k
                new_name = f"<{k}>"
                value = v
                d[new_name] = value
            else:
                name = field["name"]
                new_name = f"<{k}>{name}"
                value = field.get(v, None)
                if not value:
                    value = v
                d[new_name] = value

        return d


if __name__== '__main__':
    try:
        sended = False
        settings = fix.SessionSettings("genus_mather.cfg")
        fix_client = FixClient()
        fix_client.load_struct()
        # print("载入Fix 4.2 字典成功")
        store_factory = fix.FileStoreFactory(settings)
        log_factory = fix.ScreenLogFactory(settings)
        initiator = fix.SocketInitiator(
            fix_client, store_factory, settings, log_factory
        )
        initiator.start()

        print("系统启动成功！--------------")
        #fix_client.send_order()
        

        while True:
            time.sleep(10)
            # if not sended:
            #     fix_client.send_order()

            # #     fix_client.cancel_order()
            #     print("撤单发送完成")
            #     sended = True

    except (fix.ConfigError, fix.RuntimeError) as e:
        print(e)