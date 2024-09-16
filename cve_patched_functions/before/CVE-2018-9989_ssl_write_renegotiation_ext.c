static void ssl_write_renegotiation_ext( mbedtls_ssl_context *ssl,
                                         unsigned char *buf,
                                         size_t *olen )
{
    unsigned char *p = buf;
    const unsigned char *end = ssl->out_msg + MBEDTLS_SSL_MAX_CONTENT_LEN;

    *olen = 0;

    /* We're always including an TLS_EMPTY_RENEGOTIATION_INFO_SCSV in the
     * initial ClientHello, in which case also adding the renegotiation
     * info extension is NOT RECOMMENDED as per RFC 5746 Section 3.4. */
    if( ssl->renego_status != MBEDTLS_SSL_RENEGOTIATION_IN_PROGRESS )
        return;

    MBEDTLS_SSL_DEBUG_MSG( 3, ( "client hello, adding renegotiation extension" ) );

    if( end < p || (size_t)( end - p ) < 5 + ssl->verify_data_len )
    {
        MBEDTLS_SSL_DEBUG_MSG( 1, ( "buffer too small" ) );
        return;
    }

    /*
     * Secure renegotiation
     */
    *p++ = (unsigned char)( ( MBEDTLS_TLS_EXT_RENEGOTIATION_INFO >> 8 ) & 0xFF );
    *p++ = (unsigned char)( ( MBEDTLS_TLS_EXT_RENEGOTIATION_INFO      ) & 0xFF );

    *p++ = 0x00;
    *p++ = ( ssl->verify_data_len + 1 ) & 0xFF;
    *p++ = ssl->verify_data_len & 0xFF;

    memcpy( p, ssl->own_verify_data, ssl->verify_data_len );

    *olen = 5 + ssl->verify_data_len;
}
