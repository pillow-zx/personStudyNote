### 		解决无法从aur下载的问题



#### 一. 尝试从aur直接下载文件并在本地编译成pacman可以安装的安装包



1. 在包管理界面中找到个Git Clone URL部分， 点击复制



2. 在终端中输入：

    



```bash
git clone +[path copied just now]
```



3.将资源编译成pacman可以安装的安装包

进入clone下来的文件夹，打开终端并输入：

```bash
fingerprint-gui

makepkg -si
```



安装完毕



#### 二. 解决使用此方法时无法通过网络下载资源文件的问题



从 archlinux AUR 源下载的资源中可能包含一部分来自 [github](https://zhida.zhihu.com/search?content_id=187130671&content_type=Article&match_order=1&q=github&zd_token=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJ6aGlkYV9zZXJ2ZXIiLCJleHAiOjE3NDI5NjMyMDUsInEiOiJnaXRodWIiLCJ6aGlkYV9zb3VyY2UiOiJlbnRpdHkiLCJjb250ZW50X2lkIjoxODcxMzA2NzEsImNvbnRlbnRfdHlwZSI6IkFydGljbGUiLCJtYXRjaF9vcmRlciI6MSwiemRfdG9rZW4iOm51bGx9.A5enanQlov1MzZwKwFZJ709m1zAc0buw14ZcMnhSgZs&zhida_source=entity) 等网站的网络资源（如源代码），在使用makepkg -si命令生成安装包时，可能会发生从网络获取文件失败的现象（网络连接超时/time out）。这可能是因为该地址需要科学上网才能访问，甚至有些时候科学上网也无法访问。关于这类问题的解决方法如下：

在 “一. 尝试从aur直接下载文件并在本地编译成pacman可以安装的安装包“ 执行过

```bash
makepkg -si
```

并显示链接超时的时候会在终端上显示超时的链接

1. 下载资源文件

复制链接并粘贴到浏览器中将文件下载到本地，然后将该文件移动到解压后的aur资源文件夹中



2. 编辑PKGBUID文件

用文本编辑器打开PKGBUILD文件，找到source=（...）一栏，将原来通过网络获取的文件注释掉，并在括号中加入自己下载的文件，别忘了加上双引号

3. 安装

在clone下载的aur文件中重新输入：

```bash
makepkg -si
```

即可完成安装