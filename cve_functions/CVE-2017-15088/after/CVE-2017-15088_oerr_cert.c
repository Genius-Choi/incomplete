oerr_cert(krb5_context context, krb5_error_code code, X509_STORE_CTX *certctx,
          const char *msg)
{
    int depth = X509_STORE_CTX_get_error_depth(certctx);
    int err = X509_STORE_CTX_get_error(certctx);
    const char *errstr = X509_verify_cert_error_string(err);

    return oerr(context, code, _("%s (depth %d): %s"), msg, depth, errstr);
}
