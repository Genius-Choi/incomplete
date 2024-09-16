static authz_status ssl_authz_require_ssl_check(request_rec *r,
                                                const char *require_line,
                                                const void *parsed)
{
    SSLConnRec *sslconn = myConnConfig(r->connection);
    SSL *ssl = sslconn ? sslconn->ssl : NULL;

    if (ssl)
        return AUTHZ_GRANTED;
    else
        return AUTHZ_DENIED;
}
