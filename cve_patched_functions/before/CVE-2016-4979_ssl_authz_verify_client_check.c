static authz_status ssl_authz_verify_client_check(request_rec *r,
                                                  const char *require_line,
                                                  const void *parsed)
{
    SSLConnRec *sslconn = myConnConfig(r->connection);
    SSL *ssl = sslconn ? sslconn->ssl : NULL;

    if (!ssl)
        return AUTHZ_DENIED;

    if (sslconn->verify_error == NULL &&
        sslconn->verify_info == NULL &&
        SSL_get_verify_result(ssl) == X509_V_OK)
    {
        X509 *xs = SSL_get_peer_certificate(ssl);

        if (xs) {
            X509_free(xs);
            return AUTHZ_GRANTED;
        }
        else {
            X509_free(xs);
        }
    }

    return AUTHZ_DENIED;
}
