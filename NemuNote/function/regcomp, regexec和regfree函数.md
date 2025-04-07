# regcomp, regexec和regfree函数

标准的C和C++都不支持正则表达式，但有一些函数库可以辅助C/C++程序员完成这一功能，其中最著名的当数Philip Hazel的Perl-Compatible Regular Expression库，许多Linux发行版本都带有这个函数库。

C语言处理正则表达式常用的函数有regcomp()、regexec()、regfree()和regerror()，一般分为三个步骤，如下所示：

**C语言中使用正则表达式一般分为三步：**
1. 编译正则表达式 regcomp()
2. 匹配正则表达式 regexec()
3. 释放正则表达式 regfree()

1. 1. 编译正则表达式 regcomp()
2. 2. 匹配正则表达式 regexec()
3. 3. 释放正则表达式 regfree()

**下边是对三个函数的详细解释**

1、int regcomp (regex_t *compiled, const char *pattern, int cflags)

这个函数把指定的正则表达式pattern编译成一种特定的数据格式compiled，这样可以使匹配更有效。函数regexec 会使用这个数据在目标文本串中进行模式匹配。执行成功返回０。

**参数说明：**

①regex_t 是一个结构体数据类型，用来存放编译后的正则表达式，它的成员re_nsub 用来存储正则表达式中的子正则表达式的个数，子正则表达式就是用圆括号包起来的部分表达式。

②pattern 是指向我们写好的正则表达式的指针。

③cflags 有如下4个值或者是它们或运算(|)后的值：

REG_EXTENDED 以功能更加强大的扩展正则表达式的方式进行匹配。

REG_ICASE 匹配字母时忽略大小写。

REG_NOSUB 不用存储匹配后的结果。

REG_NEWLINE 识别换行符，这样'$'就可以从行尾开始匹配，'^'就可以从行的开头开始匹配。

2. int regexec (regex_t *compiled, char *string, size_t nmatch, regmatch_t matchptr [], int eflags)

当我们编译好正则表达式后，就可以用regexec 匹配我们的目标文本串了，如果在编译正则表达式的时候没有指定cflags的参数为REG_NEWLINE，则默认情况下是忽略换行符的，也就是把整个文本串当作一个字符串处理。执行成功返回０。

regmatch_t 是一个结构体数据类型，在regex.h中定义：

typedef struct

{

regoff_t rm_so;

regoff_t rm_eo;

} regmatch_t;

成员rm_so 存放匹配文本串在目标串中的开始位置，rm_eo 存放结束位置。通常我们以数组的形式定义一组这样的结构。因为往往我们的正则表达式中还包含子正则表达式。数组0单元存放主正则表达式位置，后边的单元依次存放子正则表达式位置。

**参数说明：**

①compiled 是已经用regcomp函数编译好的正则表达式。

②string 是目标文本串。

③nmatch 是regmatch_t结构体数组的长度。

④matchptr regmatch_t类型的结构体数组，存放匹配文本串的位置信息。

⑤eflags 有两个值

REG_NOTBOL 按我的理解是如果指定了这个值，那么'^'就不会从我们的目标串开始匹配。总之我到现在还不是很明白这个参数的意义；

REG_NOTEOL 和上边那个作用差不多，不过这个指定结束end of line。

3. void regfree (regex_t *compiled)

当我们使用完编译好的正则表达式后，或者要重新编译其他正则表达式的时候，我们可以用这个函数清空compiled指向的regex_t结构体的内容， 请记住，如果是重新编译的话，一定要先清空regex_t结构体。

4. size_t regerror (int errcode, regex_t *compiled, char *buffer, size_t length)

当执行regcomp 或者regexec 产生错误的时候，就可以调用这个函数而返回一个包含错误信息的字符串。

**参数说明：**

①errcode 是由regcomp 和 regexec 函数返回的错误代号。

②compiled 是已经用regcomp函数编译好的正则表达式，这个值可以为NULL。

③buffer 指向用来存放错误信息的字符串的内存空间。

④length 指明buffer的长度，如果这个错误信息的长度大于这个值，则regerror 函数会自动截断超出的字符串，但他仍然会返回完整的字符串的长度。所以我们可以用如下的方法先得到错误字符串的长度。

size_t length = regerror (errcode, compiled, NULL, 0);

据说一个好的程序员是会使用DB和Regular Expression的程序员，可见两者是多么重要。正则表达式是能极大地提高工作效率的工具，使用过Linux下各种具备RE特性的工具的人一定对此深有感触。很多语言都支持RE，用的最多的当然是脚本，其中以perl最盛。不过，用C语言来用RE不是很多见，但是有时候也很有用，我最近也是看到别人说道这个，所以搜了一些资料加上自己的体会来说一说RE在C语言里的应用。C语言本身不具备RE特性，但是有很多库，在Linux下你可以很方便的使用regex.h提供的库。我先贴一段代码展示一下RE在C语言里是怎么用的

```c
  #include<stdio.h>
  #include<sys/types.h>
  #include<regex.h>
  #include<memory.h>
  #include<stdlib.h>
  
  int main(){
  
	 char *bematch = "hhhericchd@gmail.com";
	 char *pattern = "h{3,10}(.*)@.{5}.(.*)";
	 char errbuf[1024];
	 char match[100];
	 regex_t reg;
	 int err,nm = 10;
	 regmatch_t pmatch[nm];
 
	 if(regcomp(&reg,pattern,REG_EXTENDED) < 0){
	 regerror(err,&reg,errbuf,sizeof(errbuf));
	 printf("err:%s\n",errbuf);
 }
 
	 err = regexec(&reg,bematch,nm,pmatch,0);
 
	 if(err == REG_NOMATCH){
		 printf("no match\n");
		 exit(-1);
	 } else if(err){
		 regerror(err,&reg,errbuf,sizeof(errbuf));
		 printf("err:%s\n",errbuf);
		 exit(-1);
		}
 
	 for(int i=0;i<10 && pmatch[i].rm_so!=-1;i++){
		 int len = pmatch[i].rm_eo-pmatch[i].rm_so;
		 if(len){
			 memset(match,'\0',sizeof(match));
			 memcpy(match,bematch+pmatch[i].rm_so,len);
			 printf("%s\n",match);
		 }
	 }
	 return 0;
 }
```

我打算看看一个邮件地址是否匹配我所提供的pattern。这个邮件地址是

hhhericchd@gmail.com  patern为

```
"h{3,10}(.*)@.{5}.(.*)"
我们希望匹配一个以3个h字符接着为任意字符串（可以为空）直到遇到一个@，然后接5个任意的字符和一个.号，最后再接一个字符串（可以为空），我们运行得到的结果是
hhhericchd@gmail.com
ericchd
com
我们发现，这个邮件地址被匹配了，第一行输出了，第二行和第三行分别输出的是我们希望得到的匹配的一部分，也就是在pattern中用括号括起来的部分。在这里我们还发现，在C语言里使用RE表达式的时候和通常的UNIX一般的RE表达式有区别：
第一、\{\}和\(\)需要改成{}和(),因为在C语言反斜杠是转移字符用的
第二、.不需要转义，不想UNIX的RE那样需要\.，但是?和*我没有找到该怎么用
下面贴上对以上所用函数的一些解释

```

regex的使用

需要用到以下几个函数。（定义在/usr/include/regex.h文件中）

int regcomp (regex_t *compiled, const char *pattern, int cflags) int regexec (regex_t *compiled, char *string, size_t nmatch, regmatch_t matchptr [], int eflags)

void regfree (regex_t *compiled)

size_t regerror (int errcode, regex_t *compiled, char *buffer, size_t length)

1.int regcomp (regex_t *compiled, const char *pattern, int cflags)

这个函数把指定的规则表达式pattern编译成一种特定的数据格式compiled，这样可以使匹配更有效。函数regexec 会使用这个数据在目标文

本串中进行模式匹配。执行成功返回０。

regex_t 是一个结构体数据类型，用来存放编译后的规则表达式，它的成员re_nsub 用来存储规则表达式中的子 规则表达式的个数，子规则表达式就是用圆括号包起来的部分表达式。

pattern 是指向我们写好的规则表达式的指针。

cflags 有如下4个值或者是它们或运算(|)后的值:

REG_EXTENDED 以功能更加强大的扩展规则表达式的方式进行匹配。

REG_ICASE 匹配字母时忽略大小写。

REG_NOSUB 不用存储匹配后的结果。

REG_NEWLINE 识别换行符，这样'$'就可以从行尾开始匹配，'^'就可以从行的开头开始匹配。

2. int regexec (regex_t *compiled, char *string, size_t nmatch, regmatch_t matchptr [], int eflags)

当我们编译好规则表达式后，就可以用regexec 匹配我们的目标文本串了，如果在编译规则表达式的时候没有指定cflags的参数为REG_NEWLINE，则默认情况下是忽略换行符的，也就是把整个文本串当作一个字符串处理。执行成功返回０。

regmatch_t 是一个结构体数据类型，成员rm_so 存放匹配文本串在目标串中的开始位置，rm_eo 存放结束位

置。通常我们以数组的形式定义一组这样的结构。因为往往我们的规则表达式中还包含子规则表达式。数组0单元存放主规则表达式位置，后边的单元依次存放子规则表达式位置。

compiled 是已经用regcomp函数编译好的规则表达式。

string 是目标文本串。

nmatch 是regmatch_t结构体数组的长度。

matchptr regmatch_t类型的结构体数组，存放匹配文本串的位置信息。

eflags 有两个值

REG_NOTBOL 按我的理解是如果指定了这个值，那么'^'就不会从我们的目标串开始匹配。总之我到现在还不是很明白这个参数的意义，

原文如下：

If this bit is set, then the beginning-of-line operator doesn't match the beginning of the

string (presumably  because it's not the beginning of a line).If not set, then the beginning-of-line operator

does match the beginning  of the string.

REG_NOTEOL 和上边那个作用差不多，不过这个指定结束end of line。

3. void regfree (regex_t *compiled)

当我们使用完编译好的规则表达式后，或者要重新编译其他规则表达式的时候，我们可以用这个函数清空

compiled指向的regex_t结构体的内

容，请记住，如果是重新编译的话，一定要先清空regex_t结构体。

4. size_t regerror (int errcode, regex_t *compiled, char *buffer, size_t length)

当执行regcomp 或者regexec 产生错误的时候，就可以调用这个函数而返回一个包含错误信息的字符串。

errcode 是由regcomp 和 regexec 函数返回的错误代号。

compiled 是已经用regcomp函数编译好的规则表达式，这个值可以为NULL。

buffer 指向用来存放错误信息的字符串的内存空间。

length 指明buffer的长度，如果这个错误信息的长度大于这个值，则regerror 函数会自动截断超出的字符串，但他仍然会返回完整的字符串的长度。所以我们可以用如下的方法先得到错误字符串的长度。

size_t length = regerror (errcode, compiled, NULL, 0);

regex虽然简单易用，但对正则表达式的支持不够强大，中文处理也有问题（经过试验可以引用vi的一些正则表达式编写例子），PCRE是另一个选择PCRE  （

[http://www.pcre.org](http://www.pcre.org/)

）

还有一份不错的资料http://midatl.radford.edu/docs/C/Pattern-Matching.html#Pattern-Matching