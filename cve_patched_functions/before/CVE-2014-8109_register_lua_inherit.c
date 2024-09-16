static const char *register_lua_inherit(cmd_parms *cmd, 
                                      void *_cfg,
                                      const char *arg)
{
    ap_lua_dir_cfg *cfg = (ap_lua_dir_cfg *) _cfg;
    
    if (strcasecmp("none", arg) == 0) {
        cfg->inherit = AP_LUA_INHERIT_NONE;
    }
    else if (strcasecmp("parent-first", arg) == 0) {
        cfg->inherit = AP_LUA_INHERIT_PARENT_FIRST;
    }
    else if (strcasecmp("parent-last", arg) == 0) {
        cfg->inherit = AP_LUA_INHERIT_PARENT_LAST;
    }
    else { 
        return apr_psprintf(cmd->pool,
                            "LuaInherit type of '%s' not recognized, valid "
                            "options are 'none', 'parent-first', and 'parent-last'", 
                            arg);
    }
    return NULL;
}
