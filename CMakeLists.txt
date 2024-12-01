cmake_minimum_required(VERSION 3.10)
project(SDL_Projekti)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Etsi SDL2-kirjasto
find_package(SDL2 REQUIRED)
include_directories(
                    ${SDL2_INCLUDE_DIRS}
                    libs
                    app/include
                    render/include
                    physics/include
                    data/include
                    /usr/local/include/bullet)

link_directories(/usr/local/lib)

# Etsi OpenMP-kirjasto
find_package(OpenMP REQUIRED)

# etsi bullet-kirjasto
find_package(Bullet REQUIRED)


# Etsi kaikki .cpp-tiedostot src-kansiosta
file(GLOB SOURCES   "app/main.cpp")

# Luo suoritettava tiedosto
add_executable(SDL_Projekti ${SOURCES})

# Linkitä SDL2-kirjasto projektiin
target_link_libraries(SDL_Projekti ${SDL2_LIBRARIES})

# Linkitä openmp-kirjasto projektiin
target_link_libraries(SDL_Projekti OpenMP::OpenMP_CXX)

find_package(glm REQUIRED)
target_link_libraries(SDL_Projekti glm::glm)

#linkitä bullet-kirjasto projektiin
target_link_libraries(SDL_Projekti BulletDynamics BulletCollision LinearMath)


