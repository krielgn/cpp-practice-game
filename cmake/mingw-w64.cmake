set(CMAKE_SYSTEM_NAME Windows)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")

set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
set(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)

# Don't try to execute Windows binaries during CMake's configure step.
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)