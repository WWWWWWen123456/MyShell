# myshell:BuiltinCommand.cpp BuiltinCommand.h Command.h ExternalCommand.cpp ExternalCommand.h Shell.cpp Shell.h main.cpp
# 	g++ -o $@ $^ -std=c++11

# .PHONY:clean
# clean:
# 	rm -f myshell
# 定义目标文件
TARGET = myshell 

# 定义编译器和编译选项
CXX = g++
CXXFLAGS = -std=c++11

# 定义源文件和头文件
SRCS = BuiltinCommand.cpp ExternalCommand.cpp Shell.cpp main.cpp
HDRS = BuiltinCommand.h Command.h ExternalCommand.h Shell.h

# 生成目标文件列表
OBJS = $(SRCS:.cpp=.o)

# 默认目标
all: $(TARGET)

# 生成目标可执行文件
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# 编译每个源文件为目标文件
%.o: %.cpp $(HDRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理生成的文件
.PHONY: clean
clean:
	rm -f $(OBJS) $(TARGET)
