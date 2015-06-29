//
//  Manual.cpp
//  HLua
//
//  Created by HSoul on 15/6/24.
//  Copyright (c) 2015年 HSoul. All rights reserved.
//

#include "Manual.h"
#include "lua.hpp"
#include <math.h>

// 所有注册到lua中的函数都具有相同的原型，该原型就是定义在lua.h中的lua_CFunction:
// typedef int (*lua_CFunction)(lua_State* L)
// @param lua 的状态, @return 返回压入栈中的返回结果数量

/* 
    C语言中使用静态函数的好处：
 
    1） 静态函数会被自动分配在一个一直使用的存储区，直到退出应用程序实例，避免了调用函数时压栈出栈，速度快很多。
 
    2） 关键字“static”，译成中文就是“静态的”，所以内部函数又称静态函数。但此处“static”的含义不是指存储方式，而是指对函数的作用域仅局限于本文件。
 
        使用内部函数的好处是：不同的人编写不同的函数时，不用担心自己定义的函数，是否会与其它文件中的函数同名，因为同名也没有关系。
*/

static int printHello(lua_State *ls)
{
    lua_pushstring(ls, "hello world");
    
    //返回值代表向栈内压入的元素个数
    return 1;
}

static int foo(lua_State *ls)
{
    int n = lua_gettop(ls);
    if (n != 0)
    {
        int i = lua_tonumber(ls, 1);
        lua_pushnumber(ls, i+1);
        return 1;
    }
    return 0;
}

static int add(lua_State * l)
{
    int n = lua_gettop(l);
    int sum = 0;
    for (int i=0;i<n;i++)
    {
        sum += lua_tonumber(l,i+1);
    }
    if(n!=0)
    {
        lua_pushnumber(l,sum);
        return 1;
    }
    
    return 0;
}

static int l_sin(lua_State * l)
{
    double d = luaL_checknumber(l, 1);
    lua_pushnumber(l, sin(d));
    return 1;
}

//把上边的函数封装到一个模块里边
static const luaL_Reg lib[] =
{
    {"printHello", printHello},
    {"foo", foo},
    {"add", add},
    {"l_sin", l_sin},
    {nullptr, nullptr},
};

// 一个是模块注册函数luaopen_tt，我想注册一个tt模块，所以这个模块的名字就叫做luaopen_tt，
// 在Lua层require一个模块名的时候其实是去找一个函数名叫luaopen_模块名的函数，
// 所以你的模块名的函数也需要按照这种格式来写，包括参数和返回值。
int luaopen_tt(lua_State *ls)
{
    // 创建一张新的表，并把列表 l 中的函数注册进去。
    luaL_newlib(ls, lib);
    
    return 1;
}


static int foo1(lua_State *ls)
{
    int n = lua_gettop(ls);
    if (n != 0)
    {
        int i = lua_tonumber(ls, 1);
        lua_pushnumber(ls, i+1);
        return 1;
    }
    return 0;
}

static int add1(lua_State * l)
{
    int n = lua_gettop(l);
    int sum = 0;
    for (int i=0;i<n;i++)
    {
        sum += lua_tonumber(l,i+1);
    }
    if(n!=0)
    {
        lua_pushnumber(l,sum);
        return 1;
    }
    
    return 0;
}

//把上边的函数封装到一个模块里边
static const luaL_Reg lib1[] =
{
    {"foo1", foo1},
    {"add1", add1},
    {nullptr, nullptr},
};

int luaopen_mm(lua_State *ls)
{
    // 创建一张新的表，并把列表 l 中的函数注册进去。
    luaL_newlib(ls, lib1);
    
    return 1;
}

