lrmd_tls_server_key_cb(gnutls_session_t session, const char *username, gnutls_datum_t * key)
{
    return lrmd_tls_set_key(key);
}
