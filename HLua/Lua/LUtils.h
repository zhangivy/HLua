//
//  LUtils.h
//  HLua
//
//  Created by HSoul on 15/6/25.
//  Copyright (c) 2015年 HSoul. All rights reserved.
//

#ifndef __HLua__LUtils__
#define __HLua__LUtils__

#include <stdarg.h>
#include <map>

class lua_State;

typedef  int (*lua_register)(lua_State *);

class LUtils final
{
public:
    static void callFunc(lua_State *ls, const char *func, const char *sig, ... );
    
    static void loadManaulLibrary(lua_State *ls, const std::map<const char *, lua_register> &registerConfig);

};

#endif /* defined(__HLua__LUtils__) */
