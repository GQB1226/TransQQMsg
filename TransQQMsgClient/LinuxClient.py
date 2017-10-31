# -*- coding: utf-8 -*-
__author__ = 'gqb1226'
import os
import socket
s=socket.socket()
port=12260
s.bind(('',port))
s.listen(5)
while True:
    conn,addr=s.accept()
    while True:
        data=conn.recvfrom(1024)
        if len(data[0])<=0:
            break
        os.system('zenity --notification --window-icon="info" --text="有QQ消息了" ')