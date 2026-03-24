cmake_minimum_required(VERSION 3.10)
project(MyTensor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 开启所有警告，Infra 工程师必须习惯 0 警告
if(MSVC)
    add_compile_options(/W3 /WX)
else()
    add_compile_options(-Wall -Wextra -Werror)
endif()

# 添加可执行文件
add_executable(my_tensor main.cpp)

# 如果之后有多线程，解除下面的注释
# find_package(Threads REQUIRED)
# target_link_libraries(my_tensor Threads::Threads)