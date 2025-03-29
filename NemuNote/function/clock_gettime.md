# clock_gettime详解

`clock_gettime` 是一个 POSIX 标准函数，用于获取高精度时间。

## 函数原型

```c
int clock_gettime(clockid_t clk_id, struct timespec *tp);
```

## 函数参数

1. `clk_id`：指定要使用的时钟类型，常见的有：
   - `CLOCK_REALTIME`：系统实时时间，可能会受到系统时间调整的影响
   - `CLOCK_MONOTONIC`：单调递增时钟，不受系统时间调整影响，但会受到系统挂起的影响
   - `CLOCK_MONOTONIC_RAW`：纯硬件时间源，不受任何系统时间调整影响
   - `CLOCK_MONOTONIC_COARSE`：低精度但高效的单调时钟，适合不需要纳秒级精度的场景
   - `CLOCK_BOOTTIME`：类似 `CLOCK_MONOTONIC`，但包含系统休眠时间
   - `CLOCK_PROCESS_CPUTIME_ID`：调用进程的 CPU 时间
   - `CLOCK_THREAD_CPUTIME_ID`：调用线程的 CPU 时间
2. `tp`：指向 `struct timespec` 结构体的指针，用于存储获取到的时间

## 返回值

- 成功：返回 0
- 失败：返回 -1，并设置 `errno` 变量



NEMU 使用 `CLOCK_MONOTONIC_COARSE` 时钟，这是一个特点如下的时钟源：

1. **单调性**：确保时间总是向前推进，不会因系统时间调整而跳跃
2. **低精度高效率**：与其他时钟源相比，获取时间的系统调用开销更小
3. **足够精确**：虽然精度稍低，但对于大多数应用场景已经足够