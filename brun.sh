#!/bin/bash

# Tarkista, onko build-kansio jo olemassa
if [ ! -d "build" ]; then
  echo "Luodaan build-kansio..."
  mkdir build
fi

# Siirry build-kansioon
cd build

# Suorita CMake-komento
echo "Suoritetaan CMake..."
cmake ..

# Tarkista, onnistuiko CMake-komento
if [ $? -ne 0 ]; then
  echo "CMake epäonnistui."
  exit 1
fi

# Suorita make-komento
echo "Käännetään projekti..."
make

# Tarkista, onnistuiko käännös
if [ $? -ne 0 ]; then
  echo "Käännös epäonnistui."
  exit 1
fi

# Suorita käännetty ohjelma
echo "Ajetaan ohjelma..."
./SDL_Projekti

