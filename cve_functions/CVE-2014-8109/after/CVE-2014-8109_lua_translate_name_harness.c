static int lua_translate_name_harness(request_rec *r)
{
    return lua_request_rec_hook_harness(r, "translate_name", APR_HOOK_MIDDLE);
}
