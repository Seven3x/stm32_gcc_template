# STM32 工程模板 (gcc + cmake)
---
###  描述
> 该工程使用 `gcc-arm-none-eabi` 编译，支持使用 `openocd` 烧录，面向 `stm32f103` 系列芯片
> 编译前需安装 `gcc-arm-none-eabi` 及 Cmake
> 烧录前需安装 `openocd`

---

**本文档基于 linux**

### 1. 使用
#### 1.1 编译
- 在终端输入 `git clone https://github.com/MagiL0/stm32_gcc_template.git`
- 在该文件夹打开终端，输入
  ```bash
  cd build
  cmake ..
  make
  ```
    终端输出无 warning 及 error 时说明没有问题，生成的 `.hex` `.elf` 等文件在你的当前文件夹 (`build`) 中。
#### 1.2 烧录
- 连接 jlink 或 stlink。
- 在终端输入
  ```bash
  openocd -f jlink.cfg -f stm32f1x.cfg
  # 如果使用 stlink，则输入：
  # openocd -f stlink.cfg -f stm32f1x.cfg
- 不要退出，打开新的命令行终端，输入 `telnet localhost 4444`
- 成功连接后输入行显示 `>`
- 输入 `program led_test.elf` 开始烧录
- 烧录成功后，输入 `restart` 程序开始执行 
- 更多详细的步骤如调试等，请查询 `openocd` 教程

### 2. 修改工程
#### 2.1 修改工程名称
- 打开 `CMakeLists.txt` ，修改第 7 行中的 `led_test` 为你自己的工程名
- 删除 `build` 文件夹中的所有内容
- 重新编译 (参考 [1.1](#11-编译))
#### 2.2 添加文件
- ##### 2.2.1 不修改文件夹目录
    * 无需修改，直接把所需 `.c, .h` 文件扔进子目录 (如 `USER/`) 即可
    * 如果是细分了 `src` `inc` 的文件夹，`.s, .c` 扔进 `src`，`.h` 扔进 `inc`
- ##### 2.2.2 修改文件夹目录
    * 当添加文件夹后在新增的文件夹里添加工程文件时，需作以下修改：
        * 添加**源文件**时，编辑 `CMakeLists.txt`。在 65 行：`file(GLOB_RECURSE SOURCES` 后添加 `.c` 文件所在的目录。
            * 如：在 `USER` 中新建 `src` 目录存放 `.c` 文件，则需修改为：
            ```cmake
            file(GLOB_RECURSE SOURCES 
                "CORE/*.c"
                "SYSTEM/delay/*.c"
                "SYSTEM/usart/*.c"
                "SYSTEM/sys/*.c"
                "USER/*.c"
                "STM32F10x_FWLib/src/*.c"
                "USER/src/*.c"
                )
            ```
        * 添加**头文件**时，编辑 `CMakeLists.txt`。在第 55 行 `include_directories` 的括号后添加 `.h` 文件目录即可。
        * 添加**汇编语言文件**时，编辑 `CMakeLists.txt`。在第 82 行 `list` 的括号中末尾处添加 `.s` 文件路径即可
        * 以上修改时可以不加引号，但若文件目录名称中含有空格，则必须添加引号。
#### 2.2 修改文件夹名称
- 当修改文件夹名称时，将 `CMakeLists.txt` 中的所有被修改的文件夹名称全部修改为被修改后的。

#### 2.3 修改单片机型号
- 使用 `stm32f103` 中的 `c, d, e, f, g` 系列时无需修改。
- 使用 `stm32f103` 中的 `8, b` 系列时需打开 `CMakeLists.txt`，修改第 22 行的 `STM32F10X_HD` 为 `STM32F10X_MD`