static int lua_auth_checker_harness(request_rec *r)
{
    return lua_request_rec_hook_harness(r, "auth_checker", APR_HOOK_MIDDLE);
}
