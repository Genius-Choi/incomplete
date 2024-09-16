static const char *register_package_cdir(cmd_parms *cmd, 
                                         void *_cfg,
                                         const char *arg)
{
    ap_lua_dir_cfg *cfg = (ap_lua_dir_cfg *) _cfg;

    return register_package_helper(cmd, arg, cfg->package_cpaths);
}
