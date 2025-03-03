# 定义编辑器
CC = gcc

# 定义编译选项
CFLAGS = -Wall -g

# 定义可执行文件名
TARGET = main

# 定义源文件
SOURCES = *.c

# 定义目标文件
OBJECTS = $(SORCES.c = .o)

# 默认目标
all: $(TARGET)

# 生成可执行文件
$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
	rm -f $(OBJECTS)

# 生成目标文件
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理可执行文件
clean:
	rm -f $(TARGET)
