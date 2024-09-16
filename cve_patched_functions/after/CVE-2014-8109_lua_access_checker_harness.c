static int lua_access_checker_harness(request_rec *r)
{
    return lua_request_rec_hook_harness(r, "access_checker", APR_HOOK_MIDDLE);
}
