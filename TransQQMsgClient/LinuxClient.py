# -*- coding: utf-8 -*-
__author__ = 'gqb1226'
import os
import socket
import logging
import time


def main():
    logging.basicConfig(filename="./server.log", level=logging.WARNING)
    s = socket.socket()
    port = 12260
    s.bind(('', port))
    s.listen(5)
    while True:
        conn, addr = s.accept()
        logging.warning('%s %s connected' % (addr, time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())))
        while True:
            try:
                data = conn.recv(1024)
            except:
                logging.warning('%s %s lost connect' % (addr, time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())))
                break
            if len(data) <= 0:
                logging.error('%s %s lost connect' % (addr, time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())))
                break
            str = data.decode("GB2312")
            # 2017-11-09 GQB1226 add心跳包,格式 hb:客户端发送的随机散列值
            if str.startswith(('hb:')):
                logging.info("%s %s send heartbeat pack" % (addr, time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())))
                conn.send(b"hb:" + str.split(":")[1].encode(encoding="utf-8"))
                continue
            os.system('zenity --notification --window-icon="info" --text="有QQ消息了" ')


if __name__ == '__main__':
    main()
