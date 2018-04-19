#include "LuaMath.h"
#include <iostream>

LuaMath::Math::Math()
{
}

LuaMath::Math::~Math()
{
}

void LuaMath::Math::pushLuaFunctions(lua_State * L)
{
	lua_pushlightuserdata(L, this);
	lua_pushcclosure(L, LuaMath::Math::luaGetLenghtTo, 1);
	lua_setglobal(L, "LuaGetLenghtTo");
}

double LuaMath::Math::getLenghtTo(const double x1, const double y1, const double x2, const double y2) const
{
	float posX = (x1 - x2);
	float posY = (y1 - y2);
	return std::sqrt(std::pow(posX, 2) + std::pow(posY, 2));
}

int LuaMath::Math::luaGetLenghtTo(lua_State * L)
{
	if (lua_isnumber(L, -1) && lua_isnumber(L, -2) && lua_isnumber(L, -3) && lua_isnumber(L, -4))
	{
		LuaMath::Math * p = static_cast<LuaMath::Math*>(lua_touserdata(L, lua_upvalueindex(1)));
		double lenght = p->getLenghtTo(lua_tonumber(L, -4), lua_tonumber(L, -3), lua_tonumber(L, -2), lua_tonumber(L, -1));
		
		lua_pop(L, 4);
		lua_pushnumber(L, lenght);

		return 1;
	}
	else
	{
		std::cout << "Error: Expected luaGetLenghtTo(double, double, double, double, double)" << std::endl;
	}
	return 0;
}
