# regcomp, regexec和 regfree 函数

**1. `regcomp` 函数**

```c
extern int regcomp(regex_t* _Restrict_ __preg,
                  const char* _Restrict_ __pattern,
                  int __cflags);
```

### 功能

- 编译正则表达式模式字符串
- 将编译后的结果存储在 regex_t 结构中

### 参数

- `__preg` : 指向 regex_t 结构的指针，用于存储编译后的正则表达式
- `__pattern`: 要编译的正则表达式模式字符串
- `__cflags`: 编译标志，可以是以下值的组合：
    - `REG_EXTENDED`: 使用扩展正则表达式语法
    - `REG_ICASE`: 忽略大小写
    - `REG_NOSUB`: 不存储匹配位置
    - `REG_NEWLINE`: 改变点号和脱字符的处理方式

**2. `regexec` 函数**

```c
extern int regexec(const regex_t* _Restrict_ __preg,
                  const char* _Restrict_ __String, 
                  size_t __nmatch,
                  regmatch_t __pmatch[],
                  int __eflags);
```

### 功能

- 使用编译好的正则表达式进行匹配

### 参数

- `__preg`: 指向已编译正则表达式的指针
- `__String`: 要匹配的目标字符串
- `__nmatch`: 可存储的最大匹配数
- `__pmatch`: 存储匹配结果的数组
- `__eflags`: 执行标志

**3. `regerror` 函数**

```c
extern size_t regerror(int __errcode,
                      const regex_t* _Restrict_ __preg,
                      char* _Restrict_ __errbuf,
                      size_t __errbuf_size);
```

### 功能

- 获取正则表达式错误的描述信息

### 参数

- `__errcode`: 错误码
- `__preg`: 产生错误的正则表达式对象
- `__errbuf`: 存储错误描述的缓冲区
- `__errbuf_size`: 缓冲区大小

## **4. `regfree` 函数**

```c
extern void regfree(regex_t* __preg);
```

### 功能

- 释放正则表达式对象占用的内存

### 参数

- `__preg`: 要释放的正则表达式对象