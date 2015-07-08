//
//  LUtils.cpp
//  HLua
//
//  Created by HSoul on 15/6/25.
//  Copyright (c) 2015年 HSoul. All rights reserved.
//

#include "lua.hpp"
#include <string.h>

void LUtils::callFunc(lua_State *ls, const char *func, const char *sig, ... )
{
    va_list vl;
    int narg, nres; // 参数和结果的数量
    
    va_start(vl, sig); // 通过两个参数，初始化vl, vl指向可变参数列表的第一个参数
    
    // 压入函数
    lua_getglobal(ls, func);
    
    // 压入参数
    for (narg = 0; *sig; narg++) // 遍历所有参数
    {
        // 检查栈中空间
        luaL_checkstack(ls, 1, "error : too many argument \n");
        
        switch (*sig++) // * 和 ++ 属于同一优先级
        {
            case 'd': // double 类型参数
                lua_pushnumber(ls, va_arg(vl, double));
                break;
                
            case 'i': // int 类型参数
                lua_pushnumber(ls, va_arg(vl, int));
                break;
                
            case 's': // 字符串 类型参数
                lua_pushstring(ls, va_arg(vl, char *));
                break;

            case '>': // 参数结束
                goto endargs;
                break;
                
            default:
                printf("invalid option (%c) \n", *(sig - 1));
        }
    }
    endargs:
    
    nres = (int)strlen(sig);
    
    // 调用函数
    if (lua_pcall(ls, narg, nres, 0) != 0)
    {
        printf("error : call function : '%s' : %s \n", func, lua_tostring(ls, -1));
    }
    
    // 检查结果
    nres = -nres; // 第一个结构栈的索引
    while (*sig)
    {
        switch (*sig++)
        {
            case 'd': // double 类型结果
                if (!lua_isnumber(ls, nres))
                {
                    printf("error : wrong result type \n");
                }
                *va_arg(vl, double*) = lua_tonumber(ls, nres);
                break;
                
            case 'i': // int 类型结果
                if (!lua_isnumber(ls, nres))
                {
                    printf("error : wrong result type \n");
                }
                *va_arg(vl, int*) = lua_tonumber(ls, nres);
                break;
                
            case 's': // 字符串 类型结果
                if (!lua_isstring(ls, nres))
                {
                    printf("error : wrong result type \n");
                }
                *va_arg(vl, const char **) = lua_tostring(ls, nres);
                break;
                
            default:
                printf("invalid option (%c) \n", *(sig - 1));
        }
    }
    
    // 清空栈
    lua_settop(ls, 0);
    
    va_end(vl);
}

void LUtils::loadManaulLibrary(lua_State *ls, const std::map<const char *, lua_register> &registerConfig)
{
    // 加载手动定义的库
    for (auto iter : registerConfig)
    {
        luaL_requiref(ls, iter.first, iter.second, 1);
        // 清空栈
        lua_settop(ls, 0);
    }
}

void LUtils::stackDump(lua_State *ls)
{
    printf("\n/**** begin dump lua stack ****/\n\n");
    int i = 0;
    
    // 获取栈顶元素的索引，索引从 1 开始
    int topIndex = lua_gettop(ls);
    
    for(i = topIndex; i >= 1; i--)
    {
        int type = lua_type(ls, i);
        
        switch (type)
        {
            case LUA_TSTRING:
            {
                printf("%d -> type : %s '%s'\n", i, lua_typename(ls, type), lua_tostring(ls, i));
                break;
            }
                
            case LUA_TBOOLEAN:
            {
                printf("%d -> type : %s '%s'\n", i, lua_typename(ls, type), lua_toboolean(ls, i) ? "true\n" : "false\n");
                break;
            }
                
            case LUA_TNUMBER:
            {
                printf("%d -> type : %s %g\n", i, lua_typename(ls, type), lua_tonumber(ls, i));
                break;
            }
                
            default:
            {
                printf("%d -> type : %s \n", i, lua_typename(ls, type));
                break;
            }
        }
    }
    printf("\n/**** end dump lua stack ****/\n\n");
}
