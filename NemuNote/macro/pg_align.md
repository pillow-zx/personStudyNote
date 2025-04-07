## 		对GNU C的\__attribute__机制的介绍

\__attribute__ 可以设置函数属性（Function Attribute ）、变量属性（Variable Attribute ）和类型属性（Type Attribute ）。

\__attribute__ 书写特征是： \_\_attribute__ 前后都有两个下划线，并且后面会紧跟一对原括弧，括弧里面是相应的\_\_attribute__ 参数。

\__attribute__ 语法格式为：\_\_attribute__ ((attribute-list))

关键字\__attribute__ 也可以对结构体（struct ）或共用体（union ）进行属性设置。大致有六个参数值可以被设定，即：aligned, packed, transparent_union, unused, deprecated 和 may_alias 。

在使用\__attribute__ 参数时，可以在参数的前后都加上“\_\_” （两个下划线），例如，使用\_\_aligned__而不是aligned ，这样，就可以在相应的头文件里使用它而不用关心头文件里是否有重名的宏定义。

**1、aligned** 

指定对象的对齐格式（以字节为单位），如：

```c
struct S {

	short b[3];

} __attribute__ ((aligned (8)));

typedef int int32_t    __attribute__((aligned(8)));
```

该声明将强制编译器确保（尽它所能）变量类 型为struct S 或者int32_t 的变量在分配空间时采用8字节对齐方式。

如上所述，可以手动指定对齐的格式，同样，也可以使用默认的对齐方式。如果aligned 后面不紧跟一个指定的数字值，那么编译器将依据你的目标机器情况使用最大最有益的对齐方式。例如

```c
struct S {

	short b[3];

} __attribute__ ((aligned));
```

这里，如果sizeof （short ）的大小为2byte，那么，S 的大小就为6 。取一个2 的次方值，使得该值大于等于6 ，则该值为8 ，所以编译器将设置S 类型的对齐方式为8 字节。

aligned 属性使被设置的对象占用更多的空间，相反的，使用packed 可以减小对象占用的空间。

需要注意的是，attribute 属性的效力与连接器也有关，如果连接器最大只支持16 字节对齐，那么你此时定义32 字节对齐也是无济于事的。

**2、packed**

​    使用该属性对struct 或者union 类型进行定义，设定其类型的每一个变量的内存约束。就是告诉编译器取消结构在编译过程中的优化对齐（使用1字节对齐）,按照实际占用字节数进行对齐，是GCC特有的语法。这个功能是跟操作系统没关系，跟编译器有关，gcc编译器不是紧凑模式的，我在windows下，用vc的编译器也不是紧凑的，用tc的编译器就是紧凑的。

​    下面的例子中，packed_struct 类型的变量数组中的值将会紧紧的靠在一起，但内部的成员变量s 不会被“pack” ，如果希望内部的成员变量也被packed 的话，unpacked-struct 也需要使用packed 进行相应的约束

1. ```c
   struct unpacked_struct
   {
   	char c;
   	int i;
   };
            
   struct packed_struct
   {
   	char c;
       int  i;
       struct unpacked_struct s;
   }__attribute__ ((__packed__));
   ```

如：

```c
在TC下：struct my{ char ch; int a;}      sizeof(int)=2;sizeof(my)=3;（紧凑模式）

在GCC下：struct my{ char ch; int a;}     sizeof(int)=4;sizeof(my)=8;（非紧凑模式）

在GCC下：struct my{ char ch; int a;}__attrubte__ ((packed))        sizeof(int)=4;sizeof(my)=5
```

下面的例子中使用__attribute__ 属性定义了一些结构体及其变量，并给出了输出结果和对结果的分析。代码为：

```c
struct p
{
    int a;
    char b;
    short c;
}__attribute__((aligned(4))) pp;
struct m
{
    char a;
    int b;
    short c;
}__attribute__((aligned(4))) mm;
struct o
{
    int a;
    char b;
    short c;
}oo;
struct x
{
    int a;
    char b;
    struct p px;
    short c;

}__attribute__((aligned(8))) xx;

int main()

{           
    printf("sizeof(int)=%d,sizeof(short)=%d.sizeof(char)=%d\n",sizeof(int)
                                                ,sizeof(short),sizeof(char));

    printf("pp=%d,mm=%d \n", sizeof(pp),sizeof(mm));
    printf("oo=%d,xx=%d \n", sizeof(oo),sizeof(xx));
    return 0;

}
```

输出结果：

sizeof(int)=4,sizeof(short)=2.sizeof(char)=1

pp=8,mm=12

oo=8,xx=24

分析：都是字节对齐的原理，可以去看这儿：[字节对齐](https://blog.csdn.net/qlexcel/article/details/79583158)

**3、at**

绝对定位，可以把变量或函数绝对定位到Flash中，或者定位到RAM。

1)、定位到flash中，一般用于固化的信息，如出厂设置的参数，上位机配置的参数，ID卡的ID号，flash标记等等

```c
const u16 gFlashDefValue[512] __attribute__((at(0x0800F000))) = {0x1111,0x1111,0x1111,0x0111,0x0111,0x0111};//定位在flash中,其他flash补充为00
const u16 gflashdata__attribute__((at(0x0800F000))) = 0xFFFF;
```

2)、定位到RAM中，一般用于数据量比较大的缓存，如串口的接收缓存，再就是某个位置的特定变量

```c
u8 USART2_RX_BUF[USART2_REC_LEN] __attribute__ ((at(0X20001000)));*//接收缓冲,最大USART_REC_LEN个字节,起始地址为0X20001000.*
```

注意：

1)、绝对定位不能在函数中定义，局部变量是定义在栈区的，栈区由MDK自动分配、释放，不能定义为绝对地址，只能放在函数外定义。

2)、定义的长度不能超过栈或Flash的大小，否则，造成栈、Flash溢出。

**4、section**

​    提到section，就得说RO RI ZI了，在ARM编译器编译之后，代码被划分为不同的段，RO Section(ReadOnly)中存放代码段和常量，RW Section(ReadWrite)中存放可读写静态变量和全局变量，ZI Section(ZeroInit)是存放在RW段中初始化为0的变量。
​    于是本文的大体意思就清晰了，__attribute__((section("section_name")))，其作用是将作用的函数或数据放入指定名为"section_name"对应的段中。

1)、编译时为变量指定段：

```c
__attribute__((section("name")))
RealView Compilation Tools for µVision Compiler Reference Guide Version 4.0 

Home > Compiler-specific Features > Variable attributes > __attribute__((section("name"))) 

4.5.6. __attribute__((section("name")))
Normally, the ARM compiler places the objects it generates in sections like data and bss. However, you might require additional data sections or you might want a variable to appear in a special section, for example, to map to special hardware. The section attribute specifies that a variable must be placed in a particular data section. If you use the section attribute, read-only variables are placed in RO data sections, read-write variables are placed in RW data sections unless you use the zero_init attribute. In this case, the variable is placed in a ZI section.

Note
This variable attribute is a GNU compiler extension supported by the ARM compiler.

Example
/* in RO section */
const int descriptor[3] __attribute__ ((section ("descr"))) = { 1,2,3 };
/* in RW section */
long long rw[10] __attribute__ ((section ("RW")));
/* in ZI section *
long long altstack[10] __attribute__ ((section ("STACK"), zero_init));/
```

2)、编译时为函数指定段

```c
__attribute__((section("name")))
RealView Compilation Tools for µVision Compiler Reference Guide Version 4.0 

Home > Compiler-specific Features > Function attributes > __attribute__((section("name"))) 

4.3.13. __attribute__((section("name")))
The section function attribute enables you to place code in different sections of the image.

Note
This function attribute is a GNU compiler extension that is supported by the ARM compiler.

Example
In the following example, Function_Attributes_section_0 is placed into the RO section new_section rather than .text.

void Function_Attributes_section_0 (void) __attribute__ ((section ("new_section")));
void Function_Attributes_section_0 (void)
{
    static int aStatic =0;
    aStatic++;
}
In the following example, section function attribute overrides the #pragma arm section setting.

#pragma arm section code="foo"
  int f2()
  {
      return 1;
  }                                  // into the 'foo' area

  __attribute__ ((section ("bar"))) int f3()
  {
      return 1;
  }                                  // into the 'bar' area

  int f4()
  {
      return 1;
  }                                  // into the 'foo' area
#pragma arm section
```

**5、多个属性，组合使用**

```c
u8 FileAddr[100] __attribute__ ((section ("FILE_RAM"), zero_init,aligned(4)));    
```