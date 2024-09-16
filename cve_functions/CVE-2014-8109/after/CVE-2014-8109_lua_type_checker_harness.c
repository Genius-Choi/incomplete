static int lua_type_checker_harness(request_rec *r)
{
    return lua_request_rec_hook_harness(r, "type_checker", APR_HOOK_MIDDLE);
}
