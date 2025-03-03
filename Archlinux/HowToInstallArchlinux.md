### 		如何安装archlinux和windows双系统

​		----文档为日后可能的重装archlinux做准备（希望不要有这种可能）。



#### **系统要求**

​	1.引导模式为UEFI，查看方法：

​		按下win+R, 在左下角弹出的框内输入msinfo32, 点击确定

​		在弹出的窗口找到BIOS模式，确定是否为UEFI

​	2.磁盘分区格式应为GPT，查看方法：

​		鼠标右键开始菜单，选择磁盘管理

​		找到window所在磁盘（以磁盘0举例）

​		鼠标右键磁盘0，选择属性并切换到卷

​		找到“磁盘分区形式”即可查看是否为GPT



#### **第一步：制作系统启动盘**

​	首先需要准备一个不小于32G的U盘并确保U盘内没有任何重要文件（U盘之后将要被清空）

​	然后到清华大学镜像站下载archlinux的iso镜像，下载地址：https://mirrors.tuna.tsinghua.edu.cn/archlinux/iso/

​	接着下载并解压ventory, 下载地址：https://www.ventoy.net/en/download.html 

​	鼠标右键开始菜单，选择磁盘管理，为你的archlinux腾出足够空间，最小40G

​	最后打开ventory，并执行：

​		1.在设备栏选择U盘（一般会显示容量，加入pc硬盘比较多，可以根据容量判断哪个是U盘）

​		2.在左上角打开配置选项，分区类型选择gpt

​		3.点击安装，之后软件让做什么就做什么（执行这一步时会清空U盘，务必检查U盘内是否有重要文件）

​		4.把下载好的iso镜像文件复制到U盘里



#### **第二步：解锁bitlocker，关闭security boot, 修改bios启动顺序**

1.解锁bitlocker

​	鼠标右键开始菜单，选择磁盘管理，在分区里查看是否有“（BitLocker 以加密）”

​	如果有bitlocker加密，执行：

​		1.在搜索栏输入“设备加密设置”并打开

​		2.在弹出的窗口中关闭“设备加密”

​		 **Worring：**加密时间与硬盘大小正相关，耗时较长，在解密过程中一定要插好电源，保持供电

​		（ 关于bitlocker详情，可参阅https://zh.wikipedia.org/wiki/BitLocker， 多说一句，这东西不只能防贼，还能防自己，非常厉害。）

2.关闭security boot

​	自行上网搜索自己pc进入bios的方式并进入bios

​	找到security boot或安全启动并将其关闭（部分主板可能在二级菜单，找不到请上网搜索）

​	保存修改

3.修改启动顺序

​	进入bios并点击startup

​	将U盘启动项放到最前面

​	保存并退出



#### **第三步：安装archlinux**

​	在修改完成启动顺序并推出后会自动进去系统引导选择界面，选择：archlinux之后一路回车



1. **连接网络及同步时间**

```bash
rfkill unblock wifi								#开启无线网卡

iwtcl											#进入联网菜单

device list										#显示网卡列表
```



输入device list后命令行会显示当前可用网卡列表，网卡排序一般是一wlan0开始，之后使用wlan0为例



```bash
station wlan0 scan && station wlan0 get-networks #搜索网络
```



这个命令输入后会显示附近当前可用的wifi列表



```bash
station wlan0 connect +[wifi name]				 #连接网络

exit											 #退出iwtcl

timedatectl										 #同步系统时间
```



**2.分配硬盘空间**

```bash
fdisk -l 										 #列出所有硬盘

cfdisk +[disk name]								 #进入硬盘空间分配界面
```

一般计算机的内置硬盘为/dev/sda，/dev/nvme0n1或/dev/mmcblk0。

​	**注意：根分区（/）和EFI分区是必须的。对于efi分区可以直接与windows的efi挂载在一起，以硬盘为/dev/nvme0n1为例，一般可以挂载到/dev/nvme0n1p1**



之后使用（这里以分配了/分区，swap分区和home分区为例）

```bash
mkfs.btrfs -f /dev/[home partition name]			 	#格式化home分区

mkswap /dev/[swap partiton name]						#格式化swap分区
```

由于我的pc在使用ext4作为分区形式时会出现无法进入系统的情况，所以这里以btrfs作为分区形式为例，如果是ext4作为分区形式的话，使用

```bash
mkfs.ext4 /dev/[home partiton name]
```

来格式化home分区，swap分区格式化方式同上。

接下来输入

```bash
mount /dev/[/ partition name] /mnt						#挂载/

mount --mkdir /dev/[home partition name] /mnt/home		#挂载home

mount --mkdi /dev/[efi system partition name] /mnt/efi	#挂载efi

swapon /dev/[swap partition name]						#挂载swap分区
```

**注意：必须先挂载根分区**

**3.配置国内镜像源**

输入

```bash
vim /etc/pacman.d/mirrorlist							
```

在第一行添加**Sever = https://mirrors.tuna.tsinghua.edu.cn/archlinux/$repo/os/$arch**

接着保存退出，在命令行输入

```bash
pacman -Syy												#刷新列表

pacman -S archlinux-keyring								#重新安装密钥
```

**4.安装必要组件并进行基础配置**

输入

```bash
pacstrap /mnt base base-devel linux-zen linux-zen-headers linux-firmware networkmanager grub os-prober efibootmgr ntfs-3g bluez bluez-utils nano vim amd-ucode 							
```

如果pc是amd的cpu最后一个就是amd-ucode ，如果是intel的cpu则用intel-ucode

只有就是有y按y,无y回车

安装完成后输入

```bash
genfsttab -U /mnt >> /mnt/etc/fstab						#自动挂载配置文件

arch-chroot /mnt										#进入系统

ln -sf /usr/share/zoneinfo/Asia/Shanghai /etc/localtime	#设置时区

hwclock --systohc										#设置硬件时间
```

接下来进行本地化，输入

```bash
vim /etc/locale.gen										
```

删除en_US.UTF-8 UTF-8和zh_CN.UTF-8 UTF-8前的“#”

保存并退出后输入

```bash
locale-gen
```

再输入

```bash
vim locale.conf 
```

添加LANG=en_US.UTF-8

接下来设置用户和root，输入

```bash
vim /etc/hostname										#设置主机名
```

给你的archlinux取个名字，保存并退出后输入

```bash
useradd -m -G wheel [user name]							#创建普通用户

passwd [user name]										#为用户创建密码
```

为用户赋予root权限

```bash
vim /etc/sudoers
```

删除%wheel ALL=(ALL:ALL) ALL前的“#”,保存并推出

接着输入

```bash
systemctl enable NetworkManager bluetooth				#启用网络和蓝牙服务
```

然后输入

```bash
vim /etc/default/grub
```

去掉GRUB_DISABLE_OS_PROBER=false前的“#”

保存并退出后输入

```bash
grub-install --target=x86_64-efi --efi-directory=/efi --bootloader-id=grub	
```

来安装grub服务，再输入

```bash
grub-mkconfig -o /boot/grub/grub.cfg					#更新grub引导
```

接下来安装kde桌面

```bash
pacman -S xorg pllasma kde-applications					#完整安装kde桌面
```

有y按y,没y回车

最后输入

```bash
systemctl enable sddm									#开机自启显示管理

exit													#退出系统

reboot													#重启
```

5.至此已经成功安装archlinux

#### **第四步：基础配置**

1.联网后打开终端，并输入：

```bash
sudo grub-mkconfig -o /boot/grub/grub.cfg			#更新启动项

sudo pacman -S adobe-source-han-sans-cn-fonts		#安装中文字体
```

2.设置中文

​	打开system setting

​	找到region and language并打开

​	修改language为简体中文并重启

3.打开终端，输入：

```bash
sudo vim /etc/pacman.conf							#配置国内源
```

去掉[mulyilib]及下一行前的“#”
然后在下面添加
**[archlinuxcn]
Server = https://mirrors.tuna.tsinghua.edu.cn/archlinuxcn/$arch
Server = https://mirrors.ustc.edu.cn/archclinuxcn/$arch
Server = https://repo.huaweicloud.com/archlinux/$repo/os/$arch**

保存并退出后输入

```bash
sudo pacman -Syy									#刷新软件包

sudo pacman -S archlinuxcn-keyring					#导入密钥

sudo pacman -S archlinux-appstream-data packagekit-qt6 fwupd #	安装后端程序

sudo pacman -S yay									#安装aur助手yay
```

4. 安装中文输入法

输入

```bash
sudo pacman -S fcitx5-im && sudo pacman -S fcitx5-chinese-addons fcitx5-rime
```

```bash
sudo vim /etc/environment
```

在末尾添加
GTK_IM_MODULE=fcitx
QT_IM_MODULE=fcitx
XMODIFIERS=@im=fcitx
SDL_IM_MODULE=fcitx
GLFW_IM_MODULE=ibus

保存并退出后输入

```bash
reboot
```

进行重启

5.安装浏览器

firefox使用

```bash
sudo pacman -S firefox
```

chrome使用

```bash
sudo pacman -S google-chrome
```

**安装配置完毕**
