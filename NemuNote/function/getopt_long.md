## 用途

`getopt`、`getopt_long`和`getopt_long_only`这三个函数是用来`解析命令行参数`的！其中getopt函数在头文件unistd.h中定义，而getopt_long和getopt_long_only在头文件getopt.h中定义。通过向这三个函数传入字符串或者结构体数组来指定我们所关心的命令行参数，就可以得到解析的结果。

`getopt`函数用于解析`单字符参数`，比如`ls`的参数`-l`、`-a`等。

`getopt_long`函数和`getopt_long_only`函数既可以解析`单字符命令行参数`，又可以解析`多字符命令行参数`。

需要说明的是这三个函数只能在`Linux/UNIX`使用！

## 1. getopt函数的用法

### 函数原型

```c
#include <unistd.h>

int getopt(int argc, char *const argv[], const char *optstring);
```

### getopt的三个参数

getopt的`argc`和`argv`参数就是`main函数`的`argc`和`argv`参数。`optstring`参数指定了我们关心的命令行选项。例如，我们写的一个程序`hello`支持两个选项`-a`和`-b`，那么optstring就可以设置为`"ab"`。getopt还支持带参数的选项。例如：

```bash
gcc helloworld.c -o helloworld
Copy
```

如果使用过GCC编译器，应该知道`-o`后面的`helloworld`是二进制文件的路径。这里的helloworld就是-o选项的参数。如果我们写的程序`hello`还有一个选项`-c`需要一个参数，那么optstring就可以是`abc:`。也就是在`c`后面加上一个`冒号:`。如果我们在`c`的后面加上两个冒号，那么参数对于`-c`选项来说就是可选的。

### 四个全局变量

getopt函数会使用到如下4个全局变量：

1. ```c
   extern char *optarg
   ```

   > optarg用来保存`选项的参数`。例如，optstring的值为`a:`，我们在终端中键入命令
   >
   > ```bash
   > hello -a hahaha
   > ```
   >
   > getopt就会将`-a`选项的参数hahaha存储到optarg。

2. ```c
   extern int optind
   ```

   > getopt会从前往后解析命令行参数，optind就是getopt已解析到的选项在`argv`的下标。

3. ```c
   extern int opterr
   ```

   > 当opterr为非零值时，getopt会将错误信息输出到`stderr`；当opterr为0时则不会输出。
   >
   > opterr的默认值为`1`。

4. ```c
   extern int optopt
   ```

   > optopt存储`解析出错的选项`。比如我们只关心`-a`、`-b`，但是传入了`-c`，则optopt会存储选项`c`。还有另一种情况就`-b`选项需要一个参数，而用户并没有为`-b`参数，那么getopt也会解析出错，并把optopt设置为`b`。

### getopt的返回值

当getopt解析到一个包含于`optstring`的选项时，会这个选项字符对应的`ASCII码`。例如解析到`-a`会返回`97`。如果解析出错，getopt会返回`?`的`ASCII码`。如果argv已经解析完成，返回`-1`。

### 举个栗子

```c
#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int c;
    while ((c = getopt(argc, argv, "ab:c::")) != -1)
    {
        switch (c)
        {
        case 'a':
            printf("选项a\n");
            break;
        case 'b':
            printf("选项b\n");
            printf("选项b的参数是: %s\n", optarg);
            break;
        case 'c':
            printf("选项c\n");
            if (optarg != NULL)
            {
                printf("选项c的参数是: %s\n", optarg);
            }
            break;
        case '?':
            printf("未知的选项: '%c'\n", c);
            break;
        }
    }

    for (int i = optind; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }

    return 0;
}
Copy
```

在上面的`getopt_test.c`中，在`optstring`设置了三个选项：不带参数`a`、带参数的`b`、以及带可选参数的`c`。然后用switch-case语句处理getopt的返回值。此外，getopt在解析命令行参数时，会`调整argv中命令行参数的顺序`。它会将每个选项及其参数放在argv的前面，将非选项放在最后。当所有的选项解析完后，`optind`就是`argv`中第一个`非选项`的下标。所以，这个for循环的用途就是输出命令行参数中所有的非选项。

下面编译一下：

```bash
gcc getopt_test.c -o getopt_test -std=gnu17 -Wall -Werror
Copy
```

在上面的shell命令中，标准设置为`gnu17`是因为`getopt`属于扩展的库函数，并非标准规定的函数。

然后运行几个样例：

```bash
./getopt_test -a -bhhh -chh
# 选项a
# 选项b
# 选项b的参数是: hhh
# 选项c
# 选项c的参数是: hh

./getopt_test -a aa -bhhh bb -chh ff
# 选项a
# 选项b
# 选项b的参数是: hhh
# 选项c
# 选项c的参数是: hh
# aa
# bb
# ff
Copy
```

对于必须有参数的选项，例如`-b`，它的参数既可以与选项分开写，也可以写在一起。（`-bhhh`，`-b hhh`都是正确的）。对于有可选参数的选项，则必须将选项和参数写在一起。

## getopt_long的用法

### 用途

`getopt`函数用来解析`单字符命令行参数`，`getopt_long`函数则同时支持`单字符命令行参数`和`多字符命令行参数`。例如`ps --help`的help参数。

### 函数原型

```c
#include <getopt.h>
int getopt_long(int argc, char *const argv[], const char *optstring, const struct option *longopts, int *longindex);
```

### 函数参数

`getopt_long`的前三个参数与`getopt`的含义相同，此处不再赘述。我们来看后两个参数。

`getopt_long`的第四个参数`longopts`是一个结构体数组。`struct option`的定义如下：

```c
struct option
{
    const char *name;
    int has_arg;
    int *flag;
    int val;
};
```

每个结构体对应了一个长选项。其中，name是长选项的名称，例如`--help`选项的name就是`help`。`has_arg`指明这个长选项是否有参数：`0`表示没有参数，`1`表示需要参数，`2`表示可选参数，在`getopt.h`分别定义了`no_argument`、`required_argument`和`optional_argument`三个宏来表示has_arg的三种可能的值。

`flag`和`val`的作用分两种情况：

1. 当flag为NULL时，如果getopt_long解析到了该长选项，则返回val。

> 前文中我曾提到，getopt返回选项字符对应的`ASCII码`。如果我们将长选项也对应一个val来返回，就可以将短选项和长选项联系在一起。

1. 当flag不为NULL时，如果getopt_long解析到了该长选项，则将val存入flag指向的地址。

> 让flag指向一个int，就可以通过检查flag来知道有没有对应的长选项的。此时getopt_long返回`0`。

getopt_long的最后一个参数用于返回长选项在longopts结构体数组中的索引值，用于调试，一般置为NULL。

### 返回值

getopt_long的返回值与getopt类似，不同的是当某个长选项的flag为NULL时，会将对应的val返回。

### 注意

getopt_long的longopts是一个结构体数组。在C语言中，我们传递数组的常用方法是传入一个指向数组的指针以及这个`数组的长度`。而在getopt_long中，并没有传入getopt_long长度，那么getopt_long如何知道这个结构体的长度呢。答案是我们传入getopt_long的结构体数组的最后一个结构体的各字段必须都为0，这样getopt_long就知道这个结构体是这个数组的结尾了。这类似于C语言中的字符串，用`\0`表示字符串的终止。

### 举个例子

```c
#include <getopt.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int c = 0;
    int flag = 0;
    struct option options[] = {{"help", required_argument, NULL, 1000},
                               {"version", optional_argument, &flag, 2000},
                               {"hello", no_argument, NULL, 3000}};
    while ((c = getopt_long(argc, argv, "ab:c::", options, NULL)) != -1)
    {
        switch (c)
        {
        case 'a':
            printf("选项a\n");
            break;
        case 'b':
            printf("选项b\n");
            printf("选项b的参数为：%s\n", optarg);
            break;
        case 'c':
            printf("选项c\n");
            if (optarg != NULL)
            {
                printf("选项c的参数为：%s\n", optarg);
            }
            break;
        case 0:
            if (flag == 2000)
            {
                printf("--version选项\n");
                if (optarg != NULL)
                {
                    printf("--version选项的参数为：%s\n", optarg);
                }
            }
            break;
        case 1000:
            printf("--help选项\n");
            printf("--help选项的参数为：%s\n", optarg);
            break;
        case 3000:
            printf("--hello选项\n");
            break;
        case '?':
            printf("未知的选项：%s\n", optarg);
            break;
        }
    }

    for (int i = optind; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }

    return 0;
}
Copy
```

需要注意的一点是，向`必须要有参数的长选项`传入参数的方法有两种：一种是将参数放在长选项的后面，例如`--help hhh`；另一种是使用`等号=`，例如，`--help=hhh`。而向`可选参数的长选项`传参数只有一种，也就是`使用等号=`。

## getopt_long_only的用法

`get_long_only`与`getopt_long`用法相似，不同的是`get_long_only`解析的长选项以一个连字符`-`开头，而`get_long`解析的长选项以两个连字符`--`开头。