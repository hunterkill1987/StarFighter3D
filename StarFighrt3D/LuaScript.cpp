#include "stdafx.h"
#include "LuaScript.h"


LuaScript::LuaScript(const std::string LuaFile)
{
	LuaState = luaL_newstate();
	if (luaL_loadfile(LuaState, LuaFile.c_str()) || lua_pcall(LuaState, 0, 0, 0))
	{
		printf("Script not Loaded: %s", LuaFile);
		LuaState = 0;
	}
}

void LuaScript::Error(const std::string Varible, const std::string Reason)
{
	printf("Error: %s, %s", Varible, Reason);
}

LuaScript::~LuaScript()
{
	if (LuaState) lua_close(LuaState);
}
