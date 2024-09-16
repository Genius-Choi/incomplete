void ff_http_init_auth_state(URLContext *dest, const URLContext *src)
{
    memcpy(&((HTTPContext *)dest->priv_data)->auth_state,
           &((HTTPContext *)src->priv_data)->auth_state,
           sizeof(HTTPAuthState));
    memcpy(&((HTTPContext *)dest->priv_data)->proxy_auth_state,
           &((HTTPContext *)src->priv_data)->proxy_auth_state,
           sizeof(HTTPAuthState));
}
