/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFLua_test.h"

ZF_NAMESPACE_GLOBAL_BEGIN

zfclass ZFLua_metatable_test : zfextends ZFFramework_test_TestCase
{
    ZFOBJECT_DECLARE(ZFLua_metatable_test, ZFFramework_test_TestCase)

protected:
    zfoverride
    virtual void testCaseOnStart(void)
    {
        zfsuper::testCaseOnStart();

        {
            ZFCoreStatisticInvokeTimeAccurateLoggerOneTime(zfText("run lua code"));
            ZFLuaExecute(zfText(
                    "print('\\n__add:')\n"
                    "print(zfint(2) + zfint(3))\n"
                    "print(zfint(2) + 3)\n"
                    "print(2 + zfint(3))\n"
                ));
            ZFLuaExecute(zfText(
                    "print('\\n__sub:')\n"
                    "print(zfint(2) - zfint(3))\n"
                    "print(zfint(2) - 3)\n"
                    "print(2 - zfint(3))\n"
                ));
            ZFLuaExecute(zfText(
                    "print('\\n__mul:')\n"
                    "print(zfint(2) * zfint(3))\n"
                    "print(zfint(2) * 3)\n"
                    "print(2 * zfint(3))\n"
                ));
            ZFLuaExecute(zfText(
                    "print('\\n__div:')\n"
                    "print(zfint(2) / zfint(3))\n"
                    "print(zfint(2) / 3)\n"
                    "print(2 / zfint(3))\n"
                ));
            ZFLuaExecute(zfText(
                    "print('\\n__mod:')\n"
                    "print(zfint(2) % zfint(3))\n"
                    "print(zfint(2) % 3)\n"
                    "print(2 % zfint(3))\n"
                ));
            ZFLuaExecute(zfText(
                    "print('\\n__unm:')\n"
                    "print(-zfint(2))\n"
                ));
            ZFLuaExecute(zfText(
                    "print('\\n__band:')\n"
                    "print(zfint(2) & zfint(3))\n"
                    "print(zfint(2) & 3)\n"
                    "print(2 & zfint(3))\n"
                ));
            ZFLuaExecute(zfText(
                    "print('\\n__bor:')\n"
                    "print(zfint(2) | zfint(3))\n"
                    "print(zfint(2) | 3)\n"
                    "print(2 | zfint(3))\n"
                ));
            ZFLuaExecute(zfText(
                    "print('\\n__bxor:')\n"
                    "print(zfint(2) ~ zfint(3))\n"
                    "print(zfint(2) ~ 3)\n"
                    "print(2 ~ zfint(3))\n"
                ));
            ZFLuaExecute(zfText(
                    "print('\\n__bnot:')\n"
                    "print(~zfint(3))\n"
                ));
            ZFLuaExecute(zfText(
                    "print('\\n__shl:')\n"
                    "print(zfint(2) << zfint(3))\n"
                    "print(zfint(2) << 3)\n"
                    "print(2 << zfint(3))\n"
                ));
            ZFLuaExecute(zfText(
                    "print('\\n__shr:')\n"
                    "print(zfint(2) >> zfint(3))\n"
                    "print(zfint(2) >> 3)\n"
                    "print(2 >> zfint(3))\n"
                ));
            ZFLuaExecute(zfText(
                    "print('\\n__concat:')\n"
                    "print(zfstring(2) .. zfstring(3))\n"
                    "print(zfstring(2) .. 3)\n"
                    "print(2 .. zfstring(3))\n"
                ));
            ZFLuaExecute(zfText(
                    "print('\\n__len:')\n"
                    "print(#zfstring('123'))\n"
                ));
            ZFLuaExecute(zfText(
                    "print('\\n__eq:')\n"
                    "print(zfint(3) == zfint(3))\n"
                    "print(zfint(3) == 3)\n" // not compared by __eq
                    "print(3 == zfint(3))\n" // not compared by __eq
                ));
            ZFLuaExecute(zfText(
                    "print('\\n__lt:')\n"
                    "print(zfint(2) < zfint(3))\n"
                    "print(zfint(2) < 3)\n"
                    "print(2 < zfint(3))\n"
                ));
            ZFLuaExecute(zfText(
                    "print('\\n__le:')\n"
                    "print(zfint(2) <= zfint(3))\n"
                    "print(zfint(2) <= 3)\n"
                    "print(2 <= zfint(3))\n"
                ));
            ZFLuaExecute(zfText(
                    "print('\\n__rt:')\n"
                    "print(zfint(4) > zfint(3))\n"
                    "print(zfint(4) > 3)\n"
                    "print(4 > zfint(3))\n"
                ));
            ZFLuaExecute(zfText(
                    "print('\\n__re:')\n"
                    "print(zfint(4) >= zfint(3))\n"
                    "print(zfint(4) >= 3)\n"
                    "print(4 >= zfint(3))\n"
                ));
            ZFLuaExecute(zfText(
                    "print('\\n__neq:')\n"
                    "print(zfint(2) ~= zfint(3))\n"
                    "print(zfint(2) ~= 3)\n"
                    "print(2 ~= zfint(3))\n"
                ));
            ZFLuaExecute(zfText(
                    "print('\\nbool:')\n"
                    "if(zfl_luaValue(zfbool('true'))) then\n"
                    "    print('bool true')\n"
                    "else\n"
                    "    print('bool false')\n"
                    "end\n"
                    "if(zfl_luaValue(zfbool('false'))) then\n"
                    "    print('bool true')\n"
                    "else\n"
                    "    print('bool false')\n"
                    "end\n"
                ));
        }

        {
            ZFCoreStatisticInvokeTimeAccurateLoggerOneTime(zfText("lua gc"));
            ZFLuaGC();
        }

        this->testCaseStop();
    }
};
ZFOBJECT_REGISTER(ZFLua_metatable_test)

ZF_NAMESPACE_GLOBAL_END

