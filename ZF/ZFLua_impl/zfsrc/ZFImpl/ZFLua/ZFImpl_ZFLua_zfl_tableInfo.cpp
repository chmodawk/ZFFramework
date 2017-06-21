/* ====================================================================== *
 * Copyright (c) 2010-2016 ZFFramework
 * home page: http://ZFFramework.com
 * blog: http://zsaber.com
 * contact: master@zsaber.com (Chinese and English only)
 * Distributed under MIT license:
 *   https://github.com/ZFFramework/ZFFramework/blob/master/license/license.txt
 * ====================================================================== */
#include "ZFImpl_ZFLua.h"

ZF_NAMESPACE_GLOBAL_BEGIN

ZFImpl_ZFLua_implSetupCallback_DEFINE(zfl_tableInfo, {
        ZFImpl_ZFLua_execute(L, zfText(
                "function zfl_tableInfo(root)\n"
                "    local cache = {  [root] = \".\" }\n"
                "    local function _dump(t,space,name)\n"
                "        local temp = {}\n"
                "        for k,v in pairs(t) do\n"
                "            local key = tostring(k)\n"
                "            if cache[v] then\n"
                "                table.insert(temp,\"+\" .. key .. \" {\" .. cache[v]..\"}\")\n"
                "            elseif type(v) == \"table\" then\n"
                "                local new_key = name .. \".\" .. key\n"
                "                cache[v] = new_key\n"
                "                table.insert(temp,\"+\" .. key .. _dump(v,space .. (next(t,k) and \"|\" or \" \" ).. string.rep(\" \",#key),new_key))\n"
                "            else\n"
                "                table.insert(temp,\"+\" .. key .. \" [\" .. tostring(v)..\"]\")\n"
                "            end\n"
                "        end\n"
                "        return table.concat(temp,\"\\n\"..space)\n"
                "    end\n"
                "    return _dump(root, \"\",\"\")\n"
                "end\n"
                "function zfl_tableInfoPrint(root)\n"
                "    print(zfl_tableInfo(root))\n"
                "end\n"
            ));
    }, {
    })

ZF_NAMESPACE_GLOBAL_END

