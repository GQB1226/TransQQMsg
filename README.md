## TransQQMsg： QQ消息提醒
主力开发环境是Debian,但是又比较依赖QQ，所以虚拟机里安装了个QQ软件，本软件的作用就是在QQ收到消息的时候通过socket发送到debian系统，然后在Debian的右上角提示有消息

* TransQQMsgServer是运行在windows端，开发环境:VS2015 MFC 
* TransQQMsgClient运行在Linux端