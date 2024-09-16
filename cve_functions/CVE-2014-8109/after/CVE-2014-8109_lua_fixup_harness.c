static int lua_fixup_harness(request_rec *r)
{
    return lua_request_rec_hook_harness(r, "fixups", APR_HOOK_MIDDLE);
}
