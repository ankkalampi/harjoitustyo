# SDL-kirjaston testailua ja käyttöönottoa

## Käyttöönotto

Aenna SDL-kirjaston uusin versio ubuntu-pohjaisessa linuxissa seuraavasti:

Päivitä pakettilistat:

 ```
 sudo apt update
 ```

Asenna SDL 2.0 ja siihen liittyvät kehitystyökalut:

```
sudo apt install libsdl2-dev
```

Luo seuraavanlainen hakemistorakenne:

```
SDL_Projekti/
├── src/
│   └── main.cpp
├── include/
│   └── oma_kirjasto.h
└── CMakeLists.txt
```

Täydennä CMakeLists.txt seuraavaan muotoon:

```
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
```




