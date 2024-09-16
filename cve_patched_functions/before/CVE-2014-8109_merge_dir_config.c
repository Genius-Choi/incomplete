static void *merge_dir_config(apr_pool_t *p, void *basev, void *overridesv)
{
    ap_lua_dir_cfg *a, *base, *overrides;

    a         = (ap_lua_dir_cfg *)apr_pcalloc(p, sizeof(ap_lua_dir_cfg));
    base      = (ap_lua_dir_cfg*)basev;
    overrides = (ap_lua_dir_cfg*)overridesv;

    a->pool = overrides->pool;
    a->dir = apr_pstrdup(p, overrides->dir);

    a->vm_scope = (overrides->vm_scope == AP_LUA_SCOPE_UNSET) ? base->vm_scope: overrides->vm_scope;
    a->inherit = (overrides->inherit == AP_LUA_INHERIT_UNSET) ? base->inherit : overrides->inherit;
    a->codecache = (overrides->codecache == AP_LUA_CACHE_UNSET) ? base->codecache : overrides->codecache;
    
    a->vm_min = (overrides->vm_min == 0) ? base->vm_min : overrides->vm_min;
    a->vm_max = (overrides->vm_max == 0) ? base->vm_max : overrides->vm_max;

    if (a->inherit == AP_LUA_INHERIT_UNSET || a->inherit == AP_LUA_INHERIT_PARENT_FIRST) { 
        a->package_paths = apr_array_append(p, base->package_paths, overrides->package_paths);
        a->package_cpaths = apr_array_append(p, base->package_cpaths, overrides->package_cpaths);
        a->mapped_handlers = apr_array_append(p, base->mapped_handlers, overrides->mapped_handlers);
        a->mapped_filters = apr_array_append(p, base->mapped_filters, overrides->mapped_filters);
        a->hooks = apr_hash_merge(p, overrides->hooks, base->hooks, overlay_hook_specs, NULL);
    }
    else if (a->inherit == AP_LUA_INHERIT_PARENT_LAST) { 
        a->package_paths = apr_array_append(p, overrides->package_paths, base->package_paths);
        a->package_cpaths = apr_array_append(p, overrides->package_cpaths, base->package_cpaths);
        a->mapped_handlers = apr_array_append(p, overrides->mapped_handlers, base->mapped_handlers);
        a->mapped_filters = apr_array_append(p, overrides->mapped_filters, base->mapped_filters);
        a->hooks = apr_hash_merge(p, base->hooks, overrides->hooks, overlay_hook_specs, NULL);
    }
    else { 
        a->package_paths = overrides->package_paths;
        a->package_cpaths = overrides->package_cpaths;
        a->mapped_handlers= overrides->mapped_handlers;
        a->mapped_filters= overrides->mapped_filters;
        a->hooks= overrides->hooks;
    }

    return a;
}
