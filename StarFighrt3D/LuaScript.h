#pragma once
#include "Engine.h"

extern "C"
{
#include "lua\include\lua.h"
#include "lua\include\lauxlib.h"
#include "lua\include\lualib.h"
}

class LuaScript
{
public:
	LuaScript(const std::string LuaFile);

	void Error(const std::string Varible, const std::string Reason);

	~LuaScript();

	bool LuaGetStock(const std::string Varible)
	{
		unsigned int Level = 0; 
		std::string var = "";
		if (LuaState != nullptr)
		{
			for (unsigned int i = 0; i < Varible.size(); i++)
			{
				if (Varible.at(i) == '.')
				{
					if (Level == 0)
					{
						lua_getglobal(LuaState, var.c_str());
					}
					else
					{
						lua_getfield(LuaState, -1, var.c_str());
					}

					if (lua_isnil(LuaState, -1))
					{
						Error(Varible,var + " Not Define");
						return false;
					}
					else
					{
						var = "";
						Level++;
					}
				}
				else
				{
					var += Varible.at(i);
				}
			}

			if (Level == 0)
			{
				lua_getglobal(LuaState, var.c_str());
			}
			else
			{
				lua_getfield(LuaState, -1, var.c_str());
			}

			if (lua_isnil(LuaState, -1))
			{
				Error(Varible, var + " Not Define");
				return false;
			}
			return true;
		}
		return false;
	}

	template<typename T>
	T Get(const std::string Varible)
	{
		if (LuaState != nullptr)
		{
			T result;

			if (LuaGetStock(Varible))
			{
				result = LuaGet<T>(Varible);
			}
			else
			{
				result = LuaGetDefault<T>();
			}
			return result;
		}
		else
		{
			Error(Varible,"Script not Loaded");
			return LuaGetDefault<T>();
		}
	}

	template<typename T>
	T LuaGetDefault()
	{
		return 0;
	}
	
	template<>
	inline bool LuaScript::LuaGet(const std::string Verible)
	{
		return (bool)lua_toboolean(LuaState, -1);
	}

	template<typename T>
	T LuaGet(const std::string Verible);

	template<>
	inline float LuaScript::LuaGet(const std::string Verible)
	{
		if (!lua_isnumber(LuaState, -1))
		{
			Error(Verible, "It's not a number");
		}
		return (float)lua_tonumber(LuaState, -1);
	}

	template<>
	inline int LuaScript::LuaGet(const std::string Verible)
	{
		if (!lua_isnumber(LuaState, -1))
		{
			Error(Verible, "It's not a number");
		}
		return (int)lua_tointeger(LuaState, -1);
	}

	template<>
	inline std::string LuaScript::LuaGet(const std::string Verible)
	{
		std::string lua_string;
		if (!lua_isinteger(LuaState, -1))
		{
			lua_string = std::string(lua_tostring(LuaState,-1));
		}
		else
		{
			Error(Verible, "It's not a string");
		}
		return lua_string;
	}


	template<>
	inline std::string LuaScript::LuaGetDefault()
	{
		return nullptr;
	}

private:
	lua_State* LuaState;
};

