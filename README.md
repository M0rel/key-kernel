# About

It is a basic kernel for a mechanical keyboard project. Idea is to create
layer between hardware and software

## Primary Setup

To be updated to reduce a required changes list

### STM32 CubeMX project

0) Setup CubeMX project && clone kernel into Src folder

1) Add sources and includes into Makefile

```shell
C_SOURCES =  \
Core/Src/key_kernel/core.c \
Core/Src/key_kernel/key_buffers_manager.c \
Core/Src/key_kernel/key_layout_provider.c \
Core/Src/key_kernel/key_manager.c \
Core/Src/key_kernel/ll_adapter.c \

...

-ICore/Src/key_kernel \
```

2) Include core.h in main.c and add user_main() call before while loop;

3) Update ll_adapter.c/h according to hardware

4) Update USB descriptor settings as in a usb.txt file
