setup_sam(void)
{
    return krb5_c_make_random_key(kdc_context, ENCTYPE_DES_CBC_MD5, &psr_key);
}
