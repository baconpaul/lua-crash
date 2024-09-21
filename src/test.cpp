#include <string>
#include <cassert>
#include <iostream>

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "luajit.h"

#include "lj_arch.h"
}

int main(int argc, char **argv)
{
 std::string fn = R"FN(
function modfunc(phase)
   if phase < 0.5 then
      return math.sin( phase * 2.0 * 3.14159 )
   else
      return -1
   end
end
)FN";

        auto cEquiv = [](float p) {
            if (p < 0.5)
                return sin(p * 2.0 * 3.14159);
            else
                return -1.0;
        };

        lua_State *L = lua_open();
	assert(L);
        luaL_openlibs(L);

        // execute script
        const char *lua_script = fn.c_str();
        int load_stat = luaL_loadbuffer(L, lua_script, strlen(lua_script), lua_script);
        lua_pcall(L, 0, 0, 0);

        // load the function from global
        int ntests = 174;
        for (int i = 0; i < ntests; ++i)
        {
            lua_getglobal(L, "modfunc");
            if (lua_isfunction(L, -1))
            {
                float p = 1.f * i / ntests;
                // push function arguments into stack
                lua_pushnumber(L, p);
                lua_pcall(L, 1, 1, 0);
                double sumval = 0.0;
                if (!lua_isnil(L, -1))
                {
                    sumval = lua_tonumber(L, -1);
                    lua_pop(L, 1);
                }
                std::cout << "At test " << i << " sum is " << sumval << std::endl;
            }
        }

        // cleanup
        lua_close(L);
}
