cmake_minimum_required(VERSION 3.10)
project(SnakeAndLadders)

# Especifica la ruta a la carpeta SDL2 en el disco C
set(SDL2_DIR "C:/SDL2")

# Incluye el directorio de encabezados de SDL2
include_directories(${SDL2_DIR}/include)

# Indica a CMake que enlace el directorio de librerías de SDL2
link_directories(${SDL2_DIR}/lib)

# Agrega el archivo fuente principal y otros archivos fuente
add_executable(SnakeAndLadders main.cpp Window.cpp Queues.cpp List.cpp)

# Enlaza las librerías de SDL2
target_link_libraries(SnakeAndLadders mingw32 SDL2main SDL2)
