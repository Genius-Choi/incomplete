lrmd_tls_server_destroy(void)
{
    if (psk_cred_s) {
        gnutls_psk_free_server_credentials(psk_cred_s);
        psk_cred_s = 0;
    }

    if (ssock > 0) {
        close(ssock);
        ssock = 0;
    }
}
