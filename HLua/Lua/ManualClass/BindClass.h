//
//  BindClass.h
//  HLua
//
//  Created by HSoul on 15/6/26.
//  Copyright (c) 2015年 HSoul. All rights reserved.
//

#ifndef __HLua__BindClass__
#define __HLua__BindClass__

#include <iostream>
#include <sstream>

class lua_State;

class Foo
{
public:
    Foo(const std::string & name) : name(name)
    {
        std::cout<< "Foo is born" << std::endl;
    }
    
    std::string Add(int a, int b)
    {
        std::stringstream ss;
        ss<< name << ": " << a << " + " << b << " = " << a + b;
        return ss.str();
    }
    
    ~Foo()
    {
        std::cout<< "Foo is gone" << std::endl;
    }
    
private:
    std::string name;
};


// interface

int l_Foo_constructor(lua_State * ls);

Foo * l_Check_Foo(lua_State *ls, int n);

int l_Foo_add(lua_State * ls);

int l_Foo_destructor(lua_State * ls);

int luaopen_lq(lua_State *ls);

#endif /* defined(__HLua__BindClass__) */
