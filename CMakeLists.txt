CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(rshell
    src/main.cpp
    src/Command.cpp
    src/Connector.cpp
    src/Shell.cpp
    src/And.cpp
    src/Or.cpp
    src/Semicolon.cpp
    src/My_In.cpp
    src/My_Out.cpp
    src/My_Out_Append.cpp
    src/My_Pipe.cpp
)

ADD_EXECUTABLE(test
    src/Command.cpp
    src/Connector.cpp
    src/Shell.cpp
    src/And.cpp
    src/Or.cpp
    src/Semicolon.cpp
    src/My_In.cpp
    src/My_Out.cpp
    src/My_Out_Append.cpp
    src/My_Pipe.cpp
    src/Command_mock.cpp
    unit_tests/test.cpp
)

TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)
