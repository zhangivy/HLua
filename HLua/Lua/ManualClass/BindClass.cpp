//
//  BindClass.cpp
//  HLua
//
//  Created by HSoul on 15/6/26.
//  Copyright (c) 2015年 HSoul. All rights reserved.
//

#include "BindClass.h"
#include "lua.hpp"

int l_Foo_constructor(lua_State * ls)
{
    const char * name = luaL_checkstring(ls, 1);
    
    Foo ** udata = (Foo **)lua_newuserdata(ls, sizeof(Foo *));
    
    *udata = new Foo(name);
    
    luaL_getmetatable(ls, "lq");
    lua_setmetatable(ls, -2);
    
    return 1;
}

int l_Foo_add(lua_State * ls)
{
    Foo *foo =  *(Foo **)luaL_checkudata(ls, 1, "lq");
    
    int a = luaL_checknumber(ls, 2);
    int b = luaL_checknumber(ls, 3);
    
    std::string s = foo->Add(a, b);
    lua_pushstring(ls, s.c_str());
    
    return 1;
}

int l_Foo_destructor(lua_State * ls)
{
    Foo *foo =  *(Foo **)luaL_checkudata(ls, 1, "lq");
    delete foo;
    
    return 0;
}

//把上边的函数封装到一个模块里边
static const luaL_Reg libFoo[] =
{
    {"new", l_Foo_constructor},
};

static const luaL_Reg lib1[] =
{
    {"add", l_Foo_add},
    {"__gc", l_Foo_destructor},
    {nullptr, nullptr},
};


int luaopen_lq(lua_State *ls)
{
    luaL_newmetatable(ls, "lq");
    lua_pushvalue(ls, -1);
    lua_setfield(ls, -2, "__index");
    luaL_setfuncs(ls, lib1, 0);
    
    // 创建一张新的表，并把列表 l 中的函数注册进去。
    luaL_newlib(ls, libFoo);
    return 1;
}

