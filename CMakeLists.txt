cmake_minimum_required(VERSION 3.10)
project(SDL_Projekti)

# Etsi SDL2-kirjasto
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} include/)

# Etsi kaikki .cpp-tiedostot src-kansiosta
file(GLOB SOURCES "src/*.cpp")

# Luo suoritettava tiedosto
add_executable(SDL_Projekti ${SOURCES})

# Linkitä SDL2-kirjasto projektiin
target_link_libraries(SDL_Projekti ${SDL2_LIBRARIES})
