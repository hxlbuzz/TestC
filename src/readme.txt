>>>>>>>>>>>>   配置修改
1.端口号修改，请修改以下【运行2】中的8521
2.修改 sh_ebin\socket_server_http\lib\sys.config 里面的端口号和证书 ，错误日志
3.修改 ebin\config 里面的证书 和 http 服务器地址，文件缓存的地址，日志地址
4.进入 sh_ebin\socket_server_http\lib 目录里

cd /var/www/sh_ebin/socket_server_http/lib/

erl -pa ./socket_server_http/ebin -pa ./simple_cache/ebin
systools:make_script("socket_server_http",[local]).

>>>>>>>>>>>>   运行
1.建立screen
screen -dmS sh1_server
screen -dmS sh1_http

2.
进入 screen -r sh1_server
进入 ebin 目录里面
输入 以下
erl +P 2000000 -env ERL_MAX_PORTS 50000 -name poker_server_webgame@127.0.0.1 -setcookie webgame
poker_server:start([8521],0).

3.
进入 screen -r sh1_http
进入 sh_ebin\socket_server_http\lib 目录里面
输入 以下
erl -name socket_server_http@127.0.0.1 -boot ./socket_server_http -config ./sys -setcookie webgame +P 2000000 -env ERL_MAX_PORTS 50000 


>>>>>>>>>>>>   启动
screen -dmS sh1_server
screen -dmS sh1_http

screen -r sh1_server
cd /var/www/ebin
erl  -name poker_server_webgame@127.0.0.1 -setcookie webgame
poker_server:start([8521],0).


screen -r sh1_http
cd /var/www/sh_ebin/socket_server_http/lib
erl -name socket_server_http@127.0.0.1 -boot ./socket_server_http -config ./sys -setcookie webgame



>>>>>>>>>>>>   http cache 使用
%% 注意顺序不可以改变！！
%% xxx:8223/server_set_value_phpstyle?key=11&value=123&time=-1
%% xxx:8223/get_value_phpstyle?key=111
%% xxx:8223/server_delete_value_phpstyle?key=111
%% 服务器设置值，用于服务器使用缓存的方式, php 形式

%% 时钟回调 php 格式 注意顺序不可以改变！！
%% 格式: xxx:8223/server_set_time_recode_phpstyle?type=Type&nsyn_id=NsynId&time=AllTime&url=HttpUrl
%% AllTime 是秒数绝对描述 HttpUrl是返回地址

%% 发送到客户端
%% 格式: xxx:8223/sm_to_client_phpstyle?id=xx&value=xxx

$ erl
1> erts_debug:df(server).
ok
2>q().
$ cat server.dis


deb http://mirrors.163.com/ubuntu/ precise main restricted universe multiverse
deb http://mirrors.163.com/ubuntu/ precise-security main restricted universe multiverse
deb http://mirrors.163.com/ubuntu/ precise-updates main restricted universe multiverse
deb http://mirrors.163.com/ubuntu/ precise-proposed main restricted universe multiverse
deb http://mirrors.163.com/ubuntu/ precise-backports main restricted universe multiverse
deb-src http://mirrors.163.com/ubuntu/ precise main restricted universe multiverse
deb-src http://mirrors.163.com/ubuntu/ precise-security main restricted universe multiverse
deb-src http://mirrors.163.com/ubuntu/ precise-updates main restricted universe multiverse
deb-src http://mirrors.163.com/ubuntu/ precise-proposed main restricted universe multiverse
deb-src http://mirrors.163.com/ubuntu/ precise-backports main restricted universe multiverse
