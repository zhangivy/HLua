//
//  LuaTest.cpp
//  HLua
//
//  Created by HSoul on 15/6/27.
//  Copyright (c) 2015年 HSoul. All rights reserved.
//

#include "LuaTest.h"
#include <map>
#include "LUtils.h"
#include "Manual.h"
#include "BindClass.h"
#include "CppClass.h"

using namespace std;

static const map<const char *, lua_register> registerConfig =
{
    {"HW",luaopen_tt},
    {"LL",luaopen_mm},
    {"cc",luaopen_student},
    {"lq", luaopen_lq},
};

void DoFile(lua_State *L, string filename)
{
    string path = "src/" + filename;
    if (luaL_dofile(L, path.c_str()))
    {
        printf("file : [%s] do failed! \n", path.c_str());
    }
}

// about lua
void luaEnter()
{
    // 1. 初始化Lua虚拟机
    lua_State *ls;
    ls = luaL_newstate();
    
    // 2. 加载标准库
    luaL_openlibs(ls);
    
    // 3. 加载手动定义的库
    LUtils::loadManaulLibrary(ls, registerConfig);
    
    stack_size
    
    // 4. 运行文件
    DoFile(ls, "moddle.lua");
        
    // 调用lua 函数
//     double result = 0;
//     LUtils::callFunc(ls, "findyou", "dd>d", 5.6, 4.4, &result);
    
    stack_size
    
    // 5. 关闭Lua虚拟机
    lua_close(ls);
}
