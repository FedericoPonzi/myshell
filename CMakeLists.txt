cmake_minimum_required(VERSION 3.8)
project(msh)
set(CMAKE_C_STANDARD 99)

include_directories(inc)
include_directories(commands/inc)
link_libraries(readline)

set(SOURCE_FILES myshell.c env.c utils.c parser.c commands/clear.c commands/clear.c commands/cd.c commands/echo.c commands/help.c signals_handlers.c inc/signals_handlers.h main.c inc/myshell.h commands/sleep.c commands/inc/sleep.h commands/exit.c commands/inc/exit.h)
add_executable(MyShell ${SOURCE_FILES})
