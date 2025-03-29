# `MUX_MACRO_PROPERTY` 宏的工作原理分析

##### `MUX_MACRO_PROPERTY` 是一个巧妙的宏，用于检测其他宏的特定属性。

### 核心定义

```c
#define MUX_MACRO_PROPERTY(p, macro, a, b) MUX_WITH_COMMA(concat(p, macro), a, b)
```

这个宏需要四个参数：

- `p`: 属性前缀（如 `__P_DEF_`、`__P_ONE_`）
- `macro`: 要检测的宏名
- `a`: 如果宏具有指定属性，返回此值
- `b`: 如果宏不具有指定属性，返回此值

## 工作流程

1. **属性检测机制**：

 定义属性占位符

```c
#define __P_DEF_0 X,  // 已定义且值为0

#define __P_DEF_1 X,  // 已定义且值为1

#define __P_ONE_1 X,  // 值为1

#define __P_ZERO_0 X,  // 值为0
```

2. **属性连接**： 通过 `concat(p, macro)` 将属性前缀和宏名连接起来，例如：

- 如果 `p` 是 `__P_DEF_` 且 `macro` 是 `FOO`，结果是 `__P_DEF_FOO`

3. **选择机制**：

```c
#define CHOOSE2nd(a, b, ...) b
#define MUX_WITH_COMMA(contain_comma, a, b) CHOOSE2nd(contain_comma a, b)
```

## 示例分析

假设我们要检测宏 `FOO` 是否已定义：

1. **如果 `FOO` 已定义为 1**：

   ```c
   MUX_MACRO_PROPERTY(__P_DEF_, FOO, "yes", "no")
   → MUX_WITH_COMMA(__P_DEF_1, "yes", "no")    // FOO被定义为1
   → MUX_WITH_COMMA(X,, "yes", "no")           // 展开__P_DEF_1
   → CHOOSE2nd(X, "yes", "no")                 // 展开MUX_WITH_COMMA
   → "yes"                                      // 最终结果
   ```

   详细解释：当定义了宏时

   ```c
   #define __P_DEF_1 X,
   ```

   这里的 `X,` 在展开时会产生一个逗号，这个逗号会被用来分隔参数。所以：

   ```c
   CHOOSE2nd(X, "yes", "no")
   ```

   这里 `X,` 展开后变成了两个参数，逗号作为参数分隔符。

   

2. **如果 `FOO` 未定义**：

```c
MUX_MACRO_PROPERTY(__P_DEF_, FOO, "yes", "no")
→ MUX_WITH_COMMA(__P_DEF_FOO, "yes", "no")  // FOO未定义
→ CHOOSE2nd(__P_DEF_FOO "yes", "no")        // 直接替换
→ "no"                                       // 最终结果
```

详细解释：当宏未定义时

```c
CHOOSE2nd(__P_DEF_FOO "yes", "no")
```

这个标识符作为一个整体，不会产生逗号，因此被视为单个参数。所以：

```c
CHOOSE2nd(__P_DEF_FOO "yes", "no")
```

这里只有两个参数，而不是三个。