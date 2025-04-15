cmake_minimum_required(VERSION 3.20)
project(lab_7)

set(CMAKE_CXX_STANDARD 17)

# Создаём исполняемый файл
add_executable(lab_7 main.cpp functions.cpp)

# Указываем путь к заголовочным файлам
target_include_directories(lab_7 PRIVATE ${CMAKE_SOURCE_DIR})

# Импортируем первую DLL (inputCheck)
add_library(InputCheck SHARED IMPORTED)
set_target_properties(InputCheck PROPERTIES
        IMPORTED_LOCATION "${CMAKE_BINARY_DIR}/libinputCheck.dll"
        IMPORTED_IMPLIB "${CMAKE_BINARY_DIR}/libinputCheck.dll.a"
)

# Импортируем вторую DLL (megagenerate)
add_library(megagenerate SHARED IMPORTED)
set_target_properties(megagenerate PROPERTIES
        IMPORTED_LOCATION "${CMAKE_BINARY_DIR}/libmegagenerate.dll"
        IMPORTED_IMPLIB "${CMAKE_BINARY_DIR}/libmegagenerate.dll.a"
)

# Линкуем обе библиотеки
target_link_libraries(lab_7 PRIVATE InputCheck megagenerate)