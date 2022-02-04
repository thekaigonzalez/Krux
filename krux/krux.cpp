#include <lua.hpp>
#include <lualib.h>
#include <lauxlib.h>

#include <iostream>
#include <fstream>
#include <filesystem>
#include <unistd.h>

namespace fs = std::filesystem;

#define KRUX_API(x) static int x(lua_State *L)

KRUX_API(krux_cpfs) {
    if (std::ifstream(luaL_checkstring(L, 1))) {
        std::cout << "krux: file/folder exists\n";
        return(0);
    } else {
        fs::copy(luaL_checkstring(L, 1), luaL_checkstring(L, 2));
        return(1);
    }
}

KRUX_API(krux_mkdir) {
    // if (std::filesystem::e)

    if (!std::ifstream(luaL_checkstring(L, 1))) {
        std::filesystem::create_directory(luaL_checkstring(L, 1));
    } else {
        std::cout << "Directory/File exists\n";
    }
    return (0);
}

KRUX_API(krux_exists) {
    lua_pushboolean(L, (bool)std::ifstream(luaL_checkstring(L, 1)));
    return 1;
}

KRUX_API(krux_rm) {
    if (std::ifstream(luaL_checkstring(L, 1))) {
        std::filesystem::remove(luaL_checkstring(L, 1));
        lua_pushboolean(L, true);
    } else {
        lua_pushboolean(L, false);
    }
    return 1;
}

KRUX_API(krux_rma) {
    if (std::ifstream(luaL_checkstring(L, 1))) {
        std::filesystem::remove_all(luaL_checkstring(L, 1));
        lua_pushboolean(L, true);
    } else {
        lua_pushboolean(L, false);
    }
    return 1;
}

KRUX_API(krux_sleep) {
    sleep(luaL_checkinteger(L, 1));
    return 1;
}

KRUX_API(krux_getcwd) {
    lua_pushstring(L, std::filesystem::current_path().c_str());
    return 1;
}

static const luaL_Reg krux[] = {
  {"cp", krux_cpfs},
  {"exists", krux_exists},
  {"getcwd", krux_getcwd},
  {"mkdir", krux_mkdir},
  {"rm", krux_rm},
  {"RemoveAll", krux_rma},
  {"sleep", krux_sleep},
  {NULL, NULL}
};


extern "C" {
    int luaopen_krux(lua_State *L) {
        luaL_newlib(L, krux);
        return 1;
    }
}