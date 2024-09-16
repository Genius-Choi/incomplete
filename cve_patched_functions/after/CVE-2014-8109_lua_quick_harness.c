static int lua_quick_harness(request_rec *r, int lookup)
{
    if (lookup) {
        return DECLINED;
    }
    return lua_request_rec_hook_harness(r, "quick", APR_HOOK_MIDDLE);
}
