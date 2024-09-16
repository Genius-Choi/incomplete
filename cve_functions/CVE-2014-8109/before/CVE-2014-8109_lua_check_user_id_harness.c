static int lua_check_user_id_harness(request_rec *r)
{
    return lua_request_rec_hook_harness(r, "check_user_id", APR_HOOK_MIDDLE);
}
