#pragma once
#include "lua.hpp"
namespace LuaMath
{
	class Math
	{
	public:
		Math();
		~Math();

		void pushLuaFunctions(lua_State * L);
	private:
		double getLenghtTo(const double x1,const double y1,const double x2,const double y2) const;
		static int luaGetLenghtTo(lua_State * L);

	};
}