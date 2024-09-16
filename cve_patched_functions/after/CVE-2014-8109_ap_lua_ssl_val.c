const char *ap_lua_ssl_val(apr_pool_t *p, server_rec *s, conn_rec *c,
                           request_rec *r, const char *var)
{
    if (lua_ssl_val) { 
        return (const char *)lua_ssl_val(p, s, c, r, (char *)var);
    }
    return NULL;
}
