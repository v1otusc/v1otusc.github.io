---
layout: post
title: Ubuntu 安装 MySQL 和简单操作
---

> [原文地址](https://www.cnblogs.com/lfri/p/10437694.html)

## 1. 安装

```bash
# 服务器
sudo apt install mysql-server
# 客户机
sudo apt install mysql-client
# 程序编译时链接的库
sudo apt install libmysqlclient-dev
```

**但是在 18.04 上并没有出现密码设置项，解决方法如下：**

找到安装时默认生成的默认账户，在终端上输入`sudo cat /etc/mysql/debian.cnf`如下图显示的账号和密码:

![](https://raw.githubusercontent.com/v1otusc/PicBed/master/mysql-installation.png
)

用得到的账户和密码登录 MySQL `mysql -u debian-sys-maint -p`，这里的密码一定要用你自己查到的那个密码，因为那是随机生成的:

![](https://raw.githubusercontent.com/v1otusc/PicBed/master/mysql-installation1.png
)

然后修改密码：

```sql
use mysql;
update mysql.user set authentication_string=password('123456') where user='root' and Host ='localhost';
update user set  plugin="mysql_native_password";
flush privileges;
quit;
```

![](https://raw.githubusercontent.com/v1otusc/PicBed/master/mysql-installation2.png
)

重启 MySQL 服务器，直接可以用 root 账户登陆了：

![](https://raw.githubusercontent.com/v1otusc/PicBed/master/mysql-installation3.png
)

安装完成之后可以使用如下命令来检查是否安装成功：

```bash
sudo netstat -tap | grep mysql
```

通过上述命令检查之后，如果看到有mysql 的 socket 处于 listen 状态则表示安装成功。然后输入下面命令登陆：

```bash
mysql -u root -p
```

-u 表示选择登陆的用户名， -p 表示登陆的用户密码，上面命令输入之后会提示输入密码，此时输入密码就可以登录到mysql。

或者这样登录：

```bash
# 服务启动后端口查询
sudo netstat -anp | grep mysql

# 连接数据库
# -h 为远程 IP，-P 为端口号，-u 为用户名，-p 为密码
mysql -h 127.0.0.1 -P 3306 -u root -p
```
MySQL 默认端口就是 **3306**。

## 2. 管理

说明：通过这种方式安装好之后开机自启动都已经配置好，命令行上的环境变量无需手动配置。

安装好之后会创建如下目录：

数据库目录：`/var/lib/mysql/ `

配置文件：`/usr/share/mysql`（命令及配置文件） ，`/etc/mysql`（如：`my.cnf`）

相关命令：`/usr/bin`(mysqladmin mysqldump等命令) 和`/usr/sbin`

启动脚本：`/etc/init.d/mysql`（启动脚本文件 mysql 的目录）

```bash
# 启动 mysql
sudo service mysql start
sudo /etc/init.d/mysql start
# 停止 mysql
sudo service mysql stop
sudo /etc/init.d/mysql stop
# 重启 mysql
sudo service mysql restart
sudo /etc/init.d/mysql restart
```

## 3. 卸载

```bash
#首先使用以下命令删除MySQL服务器：
sudo apt-get remove mysql-server
#然后，删除随MySQL服务器自动安装的任何其他软件：
sudo apt-get autoremove
#卸载其他组件：
sudo apt-get remove <package-name>
#查看从MySQL APT存储库安装的软件包列表：
dpkg -l | grep mysql | grep ii
```

## 4. 测试

`mysql -u root -p` 登陆 mysql 数据库，然后通过 `show databases`; 就可以查看当前的数据库。

![](https://raw.githubusercontent.com/v1otusc/PicBed/master/mysql-installation4.png
)

使用 `use mysql` 命令，显示当前数据库的表单：`show tables;`

![](https://raw.githubusercontent.com/v1otusc/PicBed/master/mysql-installation5.png
)
