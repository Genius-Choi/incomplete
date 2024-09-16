static int lua_request_hook(lua_State *L, request_rec *r)
{
    ap_lua_push_request(L, r);
    return OK;
}
