--[[
	lua_gettop(lua_State *L)
	
	@param

	@return 返回当前栈中的元素个数
--]]

--[[
	lua_settable(lua_State *L, int index)

	设置位于栈 index 位置 table的值。
--]]
	
	-- 例：
	lua_pushstring(ls, key); -- key 压入栈中
    lua_pushnumber(ls, value); -- value 压入栈中
    lua_settable(ls, -3);

    注：调用之后 key 和 value 出栈， table 不会变动。

--[[
	lua_gettabale

	获取栈中的值
--]]

-- 例：
	lua_getglobal( L, "global" );
	lua_pushnumber( L, 1 );

	-- 1.将刚才压栈的1弹出
	-- 2.将处于栈-2位置的global索引等于1的table存放在栈顶.
	lua_gettabale( L, -2 );

--[[
	lua_getfield

	lua 获取table值的快速方法。
--]]

	功能类似：
	lua_pushstring(L, key)
	lua_gettabale(L, -2)

	以上代码等价于：
	lua_getfield(L, -1, key)

	注：由于没有向栈中压入字符串，所以当调用lua_getfiled时，table的索引仍为-1

--[[
	lua_call

	调用一个函数。
--]]

	void lua_call (lua_State *L, int nargs, int nresults);
	
	-- 释
	要调用一个函数请遵循以下协议： 首先，要调用的函数应该被压入栈； 接着，把需要传递给这个函数的参数按正序压栈； 这是指第一个参数首先压栈。 最后调用一下 lua_call； 

	nargs 是你压入堆栈的参数个数。 

	当函数调用完毕后，所有的参数以及函数本身都会出栈。 而函数的返回值这时则被压入堆栈。 

	返回值的个数将被调整为 nresults 个， 除非 nresults 被设置成 LUA_MULTRET。 

	在这种情况下，所有的返回值都被压入堆栈中。 Lua 会保证返回值都放入栈空间中。

	函数返回值将按正序压栈（第一个返回值首先压栈）， 因此在调用结束后，最后一个返回值将被放在栈顶。

	被调用函数内发生的错误将（通过 longjmp）一直上抛。

	下面的例子中，这行 Lua 代码等价于在宿主程序用 C 代码做一些工作：

	a = f("how", t.x, 14)
	这里是 C 里的代码：

	     lua_getfield(L, LUA_GLOBALSINDEX, "f");          /* 将调用的函数 */
	     lua_pushstring(L, "how");                          /* 第一个参数 */
	     lua_getfield(L, LUA_GLOBALSINDEX, "t");          /* table 的索引 */
	     lua_getfield(L, -1, "x");         /* 压入 t.x 的值（第 2 个参数）*/
	     lua_remove(L, -2);                           /* 从堆栈中移去 't' */
	     lua_pushinteger(L, 14);                           /* 第 3 个参数 */
	     lua_call(L, 3, 1); /* 调用 'f'，传入 3 个参数，并索取 1 个返回值 */
	     lua_setfield(L, LUA_GLOBALSINDEX, "a");      /* 设置全局变量 'a' */
	注意上面这段代码是“平衡”的： 到了最后，堆栈恢复成原由的配置。 这是一种良好的编程习惯。

--[[
	lua_pcall

	以保护模式调用一个函数。
--]]
	lua_pcall (lua_State *L, int nargs, int nresults, int errfunc);

	-- 释
	nargs 和 nresults 的含义与 lua_call 中的相同。 如果在调用过程中没有发生错误， lua_pcall 的行为和 lua_call 完全一致。 

	但是，如果有错误发生的话， lua_pcall 会捕获它， 然后把单一的值（错误信息）压入堆栈，然后返回错误码。 

	同 lua_call 一样，lua_pcall 总是把函数本身和它的参数从栈上移除。

	如果 errfunc 是 0 ， 返回在栈顶的错误信息就和原始错误信息完全一致。

	否则，errfunc 就被当成是错误处理函数在栈上的索引。 （在当前的实现里，这个索引不能是伪索引。） 在发生运行时错误时， 

	这个函数会被调用而参数就是错误信息。 错误处理函数的返回值将被 lua_pcall 作为出错信息返回在堆栈上。

	典型的用法中，错误处理函数被用来在出错信息上加上更多的调试信息，比如栈跟踪信息 (stack traceback) 。 

	这些信息在 lua_pcall 返回后，因为栈已经展开 (unwound) ， 所以收集不到了。

	-- 错误信息
	lua_pcall 函数在调用成功时返回 0 ， 否则返回以下（定义在 lua.h 中的）错误代码中的一个：
	LUA_ERRRUN: 运行时错误。
	LUA_ERRMEM: 内存分配错误。 对于这种错，Lua 调用不了错误处理函数。
	LUA_ERRERR: 在运行错误处理函数时发生的错误。

--[[
	luaL_dofile 和 luaL_loadfile 的区别
--]]
luaL_dofile:
	它是这样子定义的：
	(LuaL_loadfile(L, filename) || lua_pcall(L, 0, LUA_MULTRET, 0))
	可以很明显的看出来，它不仅【加载】了，还【运行】了。
	这个函数的返回值：
		0：没有错误
		1：有错误
 
luaL_loadfile:
	（1）加载文件的时候把它当一个lua模块。它内部使用的是函数lua_load去加载名为filename的模块。如过文    件名为空，则从标准输入中加载。如果要加载的文件的第一行有符号“#”，则忽略第一行。
	（2）该函数的返回结果和lua_load返回的结果相同，但是如果打不开文件或者读取不了的时候有一个额外的错误码LUA_ERRFILE。
	（3）和lua_load一样，这个函数【只加载】，【不运行】。

可以很明显的看出来，【luaL_dofile】它不仅【加载】了，还【运行】了,而【luaL_loadfile】则【只单单加载】了而已，记忆的时候记得do多了一个运行的动作。
 
扩展：
lua_load:
	int lua_load(lua_State* L, lua_Reader reader, void* data, const char* chunkname);
	用来加载lua模块。加载如果没有错误，则lua_load将要编译的块当做lua函数压到栈顶，否则，往栈顶压错误信息。返回的结果是：
		0：没有错误
		LUA_ERRSYNTAX:预编译有语法错误
		LUA_ERRMEN:内存分配错误
	这个函数【只加载】代码块，【不运行】。
	lua_load加载的时候会自己识别加载的代码块是字符串还是二进制，并相应的加载它。
	lua_load函数使用用户提供的reader函数去读取代码块（可以去查看lua_Reader）。data作为参数传给reader函数的时候它是透明的。
	最后那个chunkname则是用来错误信息和调试信息用的。

--[[
	void luaL_newlib (lua_State *L, const luaL_Reg l[]);

	创建一张新的表，并把列表 l 中的函数注册进去。
--]]
它是用下列宏实现的：
	(luaL_newlibtable(L,l), luaL_setfuncs(L,l,0))

	数组 l 必须是一个数组，而不能是一个指针。

--[[
	void luaL_setfuncs (lua_State *L, const luaL_Reg *l, int nup);

	把数组 l 中的所有函数 （参见 luaL_Reg） 注册到栈顶的表中（该表在可选的上值之下，见下面的解说）。
--]]

若 nup 不为零， 所有的函数都共享 nup 个上值。 这些值必须在调用之前，压在表之上。 这些值在注册完毕后都会从栈弹出。

--[[
	void luaL_requiref (lua_State *L, const char *modname,lua_CFunction openf, int glb);
--]]

如果 modname 不在 package.loaded 中， 则调用函数 openf ，并传入字符串 modname。

将其返回值置入 package.loaded[modname]。 这个行为好似该函数通过 require 调用过一样。

如果 glb 为真， 同时也讲模块设到全局变量 modname 里。

在栈上留下该模块的副本。

--[[
	int lua_getglobal (lua_State *L, const char *name);

	把全局变量 name 里的值压栈，返回该值的类型。
--]]

--[[
	void luaL_checkstack (lua_State *L, int sz, const char *msg);

	将栈空间扩展到 top + sz 个元素。 如果扩展不了，则抛出一个错误。 msg 是用于错误消息的额外文本 （NULL 表示不需要额外文本）。
--]]

--[[
	-- lua 5.1 
	void luaL_register (lua_State *L, const char *libname, const luaL_Reg *l);

	Opens a library.
--]]

	When called with libname equal to NULL, it simply registers all functions in the list l (see luaL_Reg) into the table on the top of the stack.

	When called with a non-null libname, luaL_register creates a new table t, sets it as the value of the global variable libname,

	sets it as the value of package.loaded[libname], and registers on it all functions in the list l. 

	If there is a table in package.loaded[libname] or in variable libname, reuses this table instead of creating a new one.

	In any case the function leaves the table on the top of the stack.
