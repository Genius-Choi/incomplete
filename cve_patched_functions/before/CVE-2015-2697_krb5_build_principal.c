krb5_build_principal(krb5_context context,
                     krb5_principal * princ,
                     unsigned int rlen,
                     const char * realm, ...)
{
    krb5_error_code retval = 0;
    va_list ap;

    va_start(ap, realm);
    retval = krb5_build_principal_alloc_va(context, princ, rlen, realm, ap);
    va_end(ap);

    return retval;
}
