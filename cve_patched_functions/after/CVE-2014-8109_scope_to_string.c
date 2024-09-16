static const char *scope_to_string(unsigned int scope)
{
    switch (scope) {
    case AP_LUA_SCOPE_ONCE:
    case AP_LUA_SCOPE_UNSET:
        return "once";
    case AP_LUA_SCOPE_REQUEST:
        return "request";
    case AP_LUA_SCOPE_CONN:
        return "conn";
#if APR_HAS_THREADS
    case AP_LUA_SCOPE_THREAD:
        return "thread";
    case AP_LUA_SCOPE_SERVER:
        return "server";
#endif
    default:
        ap_assert(0);
        return 0;
    }
}
