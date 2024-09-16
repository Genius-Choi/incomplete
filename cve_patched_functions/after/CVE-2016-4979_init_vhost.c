static apr_status_t init_vhost(conn_rec *c, SSL *ssl)
{
    const char *servername;
    
    if (c) {
        SSLConnRec *sslcon = myConnConfig(c);
        
        if (sslcon->server != c->base_server) {
            /* already found the vhost */
            return APR_SUCCESS;
        }
        
        servername = SSL_get_servername(ssl, TLSEXT_NAMETYPE_host_name);
        if (servername) {
            if (ap_vhost_iterate_given_conn(c, ssl_find_vhost,
                                            (void *)servername)) {
                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(02043)
                              "SSL virtual host for servername %s found",
                              servername);
                return APR_SUCCESS;
            }
            else {
                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(02044)
                              "No matching SSL virtual host for servername "
                              "%s found (using default/first virtual host)",
                              servername);
                /*
                 * RFC 6066 section 3 says "It is NOT RECOMMENDED to send
                 * a warning-level unrecognized_name(112) alert, because
                 * the client's behavior in response to warning-level alerts
                 * is unpredictable."
                 *
                 * To maintain backwards compatibility in mod_ssl, we
                 * no longer send any alert (neither warning- nor fatal-level),
                 * i.e. we take the second action suggested in RFC 6066:
                 * "If the server understood the ClientHello extension but
                 * does not recognize the server name, the server SHOULD take
                 * one of two actions: either abort the handshake by sending
                 * a fatal-level unrecognized_name(112) alert or continue
                 * the handshake."
                 */
            }
        }
        else {
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(02645)
                          "Server name not provided via TLS extension "
                          "(using default/first virtual host)");
        }
    }
    
    return APR_NOTFOUND;
}
