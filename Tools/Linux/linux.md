# Linux 面试考点
## Linux 基本概念
1. Linux内核和操作系统的关系？
答： inux 内核是 Linux 操作系统的核心，提供硬件资源管理和底层控制，而 Linux 操作系统是基于 Linux 内核构建，提供用户交互、工具和应用的完整环境。

2. Linux 文件系统的结构？

答：
|目录|含义|
|--|--|
|`/`|**根目录**，Linux文件目录的起点，包含其他所有目录|
|`/bin`|**基本命令**，包含系统启动和维护所需的常用二进制文件|
|`/sbin`|**系统管理命令**，只有管理员 (root) 才能执行的系统维护命令（如 reboot, fdisk）。|
|`/boot`|**引导文件**，用于存储内核（vmlinuz）、引导加载程序（如 GRUB）和系统启动相关文件。|
|`/dev`|**设备文件**，Linux 将设备视为文件，硬盘、USB、终端等均通过此目录访问（如 /dev/sda1）。|
|`/etc`|**系统配置文件**，主要存放系统和服务的配置（如 /etc/passwd 用户信息、/etc/hosts 主机解析）。|
|`/home`|**用户主目录**，每个普通用户都有一个子目录（如 /home/user，用户数据、配置存储在此）。|
|`/root`|**超级用户主目录**，root 用户专属，类似普通用户的 /home。|
|`/lib`|**基本共享库**，存放系统核心程序依赖的共享库（如 C 标准库 libc.so）。|
|`/lib64`|**64 位共享库**，专用于 64 位系统上的共享库文件。|
|`/media`|**挂载点**，用于挂载外部存储设备（如 U 盘、光盘，通常自动挂载于此目录）。|
|`/mnt`|**临时挂载点**，用于临时挂载文件系统，如其他分区、网络共享。|
|`/opt`|**可选软件包**，第三方软件或手动安装的软件通常放置在此（如 /opt/mysql）。|
|`/proc`|**虚拟文件系统**，用于内核与进程的交互，存储系统实时信息（如 /proc/cpuinfo CPU 信息）。|
|`/sys`|**系统信息**，与 /proc 类似，提供硬件设备和驱动信息，支持热插拔管理。|
|`/tmp`|**临时文件**，用于存放临时数据，系统重启后此目录下数据会被清除。|
|`/usr`|**用户软件资源**，存放系统的共享资源和应用程序，类似于 Windows 的 "Program Files"。|
|`/var`|**动态数据**，用于存放经常变化的数据（如日志、缓存、数据库）。|
|`/var/log`|**系统日志**，如 /var/log/messages（系统日志）、/var/log/syslog（通用日志）。|
|`/var/spool`|**任务队列**，如打印机任务、邮件队列。|
|`/var/cache`|**缓存文件**，缓存数据（如 dnf、apt 软件包缓存）。|
|`/run`|**系统运行时数据**，包含与系统和服务有关的临时数据，系统重启后清空。|
|`/srv`|**服务数据**，通常存放 Web、FTP 等服务的特定数据（如 /srv/www）。|
|`/lost+found`|**恢复文件**，文件系统异常时修复的文件会存放于此，ext 文件系统特有。|

## 常用命令

1. `ls`, `cd`, `pwd`, `mkdir`, `rmdir`, `rm` 等文件操作命令。
2. `cat`, `more`, `less`, `head`, `tail` 等文件查看命令。
3. `cp`, `mv`, `touch` 等文件复制、移动和创建命令。
4. `find`, `locate` 等查找文件的命令。
5. `chmod`, `chown`, `chgrp` 等权限管理命令，使用 chmod 可以修改文件权限，chown 修改文件的所有者，chgrp 修改文件的所属组。
6. `ps`, `top`, `htop`, `kill`, `killall` 等进程管理命令。
7. `df`, `du`, `free`, `uptime` 等系统状态查看命令。

## 进程管理

1. 进程是什么？如何查看进程？
答：**进程**（Process） 是计算机中程序在**运行时的实例**，是操作系统进行资源分配的基本单位。
查看进程的命令：
- `ps`：用于查看当前系统中静态的进程快照。
- `top/htop`：实时监控系统中的进程、CPU、内存使用情况。
- `pgrep`：按名称查找正在运行的进程，返回对应的 PID。
- `pidof`：获取某个程序的 PID。

2. 进程生命周期：如何启动、停止、挂起进程？
答：

|状态|说明|
|--|--|
|**创建**|进程被创建，但未开始执行|
|**就绪**|进程准备好，等待CPU调度调度执行|
|**运行**|进程获得CPU时间片，正在执行指令|
|**阻塞**|进程等待某个事件（如I/O，信号）完成|
|**终止**|进程执行完毕或被强制结束，进入终止状态。|

启动进程： 
    - 命令行直接启动；
    - 使用`fork()`和`exec()`系统调用；
停止进程：
    - `kill` \<PID>
    - `pkill` Name
    - `systemctl` stop
    - `killall`
挂起进程：
    - `kill` -STOP <PID>  
    - `bg` %1  恢复并在后台执行
    - `fg` %1  将后台进程切换到前台
    - `jobs` 查看后台进程

3. 如何在终端关闭后保持进程运行？
答：
- `nohup`（no hang up）命令可以使一个程序在终端退出或SSH 断开后继续运行，并将其输出重定向到 nohup.out 文件（除非你另行指定）。
- `disown` 命令用于将已有的后台任务与终端解绑，确保其在终端关闭后继续运行。

4. Linux 进程间通信的方式？

## 网路管理

1. 常见网络命令

|命令|功能|
|--|--|
|`ifconfig`|用于显示和配置网络接口信息|
|`ip`|现代 Linux 系统中用于管理网络设备、路由、IP 地址等，功能更强大、灵活，已完全取代 ifconfig|
|`netstat`|用于显示网络连接、路由表、端口使用情况、网络接口统计信息。|
|`ss`|显示套接字（Socket）统计信息，查看TCP/UDP 连接、监听端口、连接状态，功能类似于 netstat，但执行速度更快。|
|`ping`|用于测试网络连通性，通过发送 ICMP 回显请求（Echo Request）来判断目标主机是否可达。|
|`traceroute`|显示数据包从本地主机到目标主机的路由路径，帮助排查网络延迟和节点问题。|
|`curl`|强大的命令行工具，用于执行 HTTP/HTTPS、FTP、SFTP 等多种协议的数据请求，支持文件下载、接口测试、REST API 调试等。|
|`wget`|主要用于从Web下载文件，支持 HTTP、HTTPS、FTP 协议，适用于批量下载、离线抓取。|

2. 网络配置文件：如何配置 IP 地址，查看路由表，配置 DNS 等。
答：
- 配置IP地址：`ip addr`
- 查看路由表：`ip route`
- 配置DNS：`/etc/resolv.conf` （临时） `/etc/netplan/00-installer-config.yaml` （永久）

## 系统管理

1. 用户与权限管理
```bash
# 添加用户
sudo useradd username

# 设置用户密码
sudo passwd username

# 删除用户（保留家目录）
sudo userdel username

# 删除用户（删除家目录）
sudo userdel -r username

# 修改用户信息（如默认 Shell、家目录）
sudo usermod -s /bin/bash username    # 修改 Shell
sudo usermod -d /new/home username   # 修改家目录

# 添加新组
sudo groupadd groupname

# 删除组
sudo groupdel groupname

# 将用户添加到组
sudo usermod -aG groupname username

# 查看用户所属组
groups username

```

2. 磁盘管理
```bash
# 查看磁盘空间使用情况
df -h

# 查看磁盘分区信息
lsblk

# 查看硬盘信息（包括型号、容量）
sudo fdisk -l

# 查看文件系统磁盘使用情况
du -sh /path/to/dir


# 创建挂载点
sudo mkdir /mnt/data

# 挂载分区
sudo mount /dev/sdb1 /mnt/data

# 查看已挂载的设备
mount

# 自动挂载（编辑 /etc/fstab 文件）
/dev/sdb1  /mnt/data  ext4  defaults  0  2

# 卸载设备
sudo umount /mnt/data

```

3. 日志管理

```bash
# 查看日志文件内容
cat /var/log/syslog

# 查看日志前 10 行
head /var/log/syslog

# 查看日志后 10 行
tail /var/log/syslog


# 实时监控日志输出
tail -f /var/log/syslog

# grep 筛选日志（如 SSH 登录失败）
grep "Failed password" /var/log/auth.log

```

## 性能监控

|监控内容|命令|
|--|--|
|CPU|`top`,`htop`,`mpstat`|
|内存和交换|`free`,`vmstat`|
|磁盘 I/O|`iostat`,`iotop`|
|网络|`ifconfig`,`ss`,`iftop`|
|系统负载与进程|`uptime`,`ps`,`pidstat`|
|历史监控|`sar`|

