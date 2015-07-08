//
//  CppClass.h
//  HLua
//
//  Created by HSoul on 15/7/8.
//  Copyright (c) 2015年 HSoul. All rights reserved.
//

#ifndef __HLua__CppClass__
#define __HLua__CppClass__

#include "lua.hpp"
#include"Student.h"

int newStudent(lua_State* L)
{
    Student **s =  (Student**)lua_newuserdata(L, sizeof(Student*));  // lua will manage Student** pointer
    *s = new Student;
    
    // 将 userdata 和 cc.Student 元表关联
    luaL_getmetatable(L, "cc.Student");
    lua_setmetatable(L, -2);
    return 1;
}

int l_setName(lua_State* L)
{
    // 这个luaL_checkudata除了可以把index为1的栈上的元素转换为userdata外，还可以检测它是否包含“cc.Student”元表，这样代码更加健壮。
    Student **s = (Student**)luaL_checkudata(L,1,"cc.Student");
    luaL_argcheck(L, s != NULL, 1, "invalid user data");
    
    luaL_checktype(L, -1, LUA_TSTRING);
    
    std::string name = lua_tostring(L, -1);
    (*s)->setName(name);
    return 0;
}

int l_setAge(lua_State* L)
{
    Student **s = (Student**)luaL_checkudata(L,1,"cc.Student");
    luaL_argcheck(L, s != NULL, 1, "invalid user data");
    luaL_checktype(L, -1, LUA_TNUMBER);
    int age = lua_tonumber(L, -1);
    (*s)->setAge(age);
    return 0;
}

int l_getName(lua_State* L)
{
    Student **s = (Student**)luaL_checkudata(L,1,"cc.Student");
    luaL_argcheck(L, s != NULL, 1, "invalid user data");
    lua_settop(L, 0);
    lua_pushstring(L, (*s)->getName().c_str());
    return 1;
}

int l_getAge(lua_State* L)
{
    Student **s = (Student**)luaL_checkudata(L,1,"cc.Student");
    luaL_argcheck(L, s != NULL, 1, "invalid user data");
    lua_settop(L, 0);
    lua_pushnumber(L, (*s)->getAge());
    return 1;
}

int l_print(lua_State* L)
{
    Student **s = (Student**)luaL_checkudata(L,1,"cc.Student");
    luaL_argcheck(L, s != NULL, 1, "invalid user data");
    (*s)->print();
    
    return 0;
}

int student2string (lua_State *L) {
    Student **s = (Student**)luaL_checkudata(L, 1, "cc.Student");
    lua_pushfstring(L, "name = %s, age = %d",(*s)->getName().c_str(), (*s)->getAge());
    
    return 1;
}

static int auto_gc(lua_State *L)
{
    Student **s = (Student**)luaL_checkudata(L,1,"cc.Student");
    if( s )
    {
        delete *s;
    }
    
    return 0;
}

static const struct luaL_Reg stuentlib_f [] =
{
    {"create", newStudent},
    {NULL, NULL}
};

static const struct luaL_Reg studentlib_m [] =
{
    {"__tostring",student2string},
    {"setName",l_setName},
    {"setAge", l_setAge},
    {"print", l_print},
    {"getName",l_getName},
    {"getAge", l_getAge},
    {"__gc", auto_gc},
    {NULL, NULL}
};

int luaopen_student (lua_State *L)
{
    // 创建元表，注册函数， 并将其放入rigistey 表中
    luaL_newmetatable(L, "cc.Student");
    /* metatable.__index = metatable */
    lua_pushvalue(L, -1);  /* duplicates the metatable */
    lua_setfield(L, -2, "__index");
    luaL_setfuncs(L, studentlib_m, 0);
    
    // 创建一个表并注册行数
    luaL_newlib(L, stuentlib_f);
    
    return 1;
}

#endif /* defined(__HLua__CppClass__) */
