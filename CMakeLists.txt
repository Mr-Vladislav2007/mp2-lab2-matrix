cmake_minimum_required(VERSION 3.14)
project(VectorMatrixTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Google Test ---
set(GTEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/gtest)

add_library(gtest_lib STATIC
  ${GTEST_DIR}/gtest-all.cc
)
target_include_directories(gtest_lib PUBLIC ${GTEST_DIR})

# Для MSVC может потребоваться этот макрос
target_compile_definitions(gtest_lib PRIVATE _VARIADIC_MAX=10)

# Рекомендуемая настройка для поиска потоков
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
target_link_libraries(gtest_lib PUBLIC Threads::Threads)

# --- Тесты ---
add_executable(run_tests
  test/test_main.cpp
  test/test_tvector.cpp
  test/test_tmatrix.cpp
)

target_include_directories(run_tests PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Принудительное включение заголовков для tmatrix.h: -include для GCC/Clang, /FI для MSVC
if(MSVC)
  target_compile_options(run_tests PRIVATE /FI cassert /FI algorithm)
else()
  target_compile_options(run_tests PRIVATE -include cassert -include algorithm)
endif()

target_link_libraries(run_tests PRIVATE gtest_lib)

enable_testing()
add_test(NAME all_tests COMMAND run_tests)