# Mettaton

Discord bot for multi-purposes
### Commands

`/neko`
Generates a neko image fecthed from [TheCatAPI](https://thecatapi.com/)

### Installation
Building is done via [CMake](https://cmake.org/)
+ requires `curl >= 8.12.0`
+ installs `dpp` version `10.1.2`
+ features `nlohmann/json` version `3.12.0`

Simply run `cmake -B build` and `cmake --build build` in `<rootDir>`. the binary will be at `<rootDir>/build/mettaton`

> [!WARNING]
> Mettaton requires `TOKEN_LOC`, `NEKOS_SOURCE`, `NEKO_STORE_LOC`, and `NEKOS_BATCH` 
> environment variables to be set. If you prefer not using docker, be sure to provide them.
