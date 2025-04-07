# struct timespec详解

struct timespec通常在头文件<time.h>中定义， 基本结构为：

```c
struct timespec {
	time_t tv_sec;		/* 秒数 */
	long   tv_nsec;		/* 纳秒数 */
}
```

## 字段解释：

1. `tv_sec`：存储整秒数，类型为 `time_t`（通常是 `long` 或 `long long`）
2. `tv_nsec`：存储纳秒数，类型为 `long`（10亿分之一秒，范围为 0-999,999,999）

## 使用方式：

```c
struct timespec now;
clock_gettime(CLOCK_MONOTONIC_COARSE, &now);
uint64_t us = now.tv_sec * 1000000 + now.tv_nsec / 1000;
```

1. 声明一个 `timespec` 类型的变量 `now`

2. 调用 `clock_gettime()` 函数填充这个结构体，获取当前时间

3. 将时间转换为微秒单位：

   - 将秒数乘以 1,000,000（转换为微秒）
   - 将纳秒数除以 1,000（转换为微秒）
   - 将两者相加得到总微秒数

   

## 使用的时钟源：

`CLOCK_MONOTONIC_COARSE` 是 Linux 特有的时钟源，具有以下特点：

- 单调递增（总是增加，不受系统时间调整的影响）
- 比标准 `CLOCK_MONOTONIC` 精度稍低但性能更好
- 适合那些不需要绝对精确度但需要高效率的计时场景

这种方法在 NEMU 中提供了一个性能和精度之间的良好平衡，适合模拟器的计时需求。



在实际应用中，当需要高精度计时但又不想因为频繁系统调用而影响性能时，这种实现方式非常实用。