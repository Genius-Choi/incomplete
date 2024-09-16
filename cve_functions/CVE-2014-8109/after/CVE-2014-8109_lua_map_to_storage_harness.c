static int lua_map_to_storage_harness(request_rec *r)
{
    return lua_request_rec_hook_harness(r, "map_to_storage", APR_HOOK_MIDDLE);
}
