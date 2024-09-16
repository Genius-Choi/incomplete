static const char *register_lua_codecache(cmd_parms *cmd, 
                                      void *_cfg,
                                      const char *arg)
{
    ap_lua_dir_cfg *cfg = (ap_lua_dir_cfg *) _cfg;
    
    if (strcasecmp("never", arg) == 0) {
        cfg->codecache = AP_LUA_CACHE_NEVER;
    }
    else if (strcasecmp("stat", arg) == 0) {
        cfg->codecache = AP_LUA_CACHE_STAT;
    }
    else if (strcasecmp("forever", arg) == 0) {
        cfg->codecache = AP_LUA_CACHE_FOREVER;
    }
    else { 
        return apr_psprintf(cmd->pool,
                            "LuaCodeCache type of '%s' not recognized, valid "
                            "options are 'never', 'stat', and 'forever'", 
                            arg);
    }
    return NULL;
}
