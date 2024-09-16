int ap_lua_ssl_is_https(conn_rec *c)
{
    return lua_ssl_is_https ? lua_ssl_is_https(c) : 0;
}
