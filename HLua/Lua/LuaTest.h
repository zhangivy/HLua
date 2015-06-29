//
//  LuaTest.h
//  HLua
//
//  Created by HSoul on 15/6/27.
//  Copyright (c) 2015年 HSoul. All rights reserved.
//

#ifndef __HLua__LuaTest__
#define __HLua__LuaTest__

#include <string>
#include "lua.hpp"

extern void DoFile(lua_State *L, std::string filename);
extern void luaEnter();

#endif /* defined(__HLua__LuaTest__) */
