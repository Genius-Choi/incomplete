prepare_enc_data(unsigned char *indata,
                 int indata_len,
                 unsigned char **outdata,
                 int *outdata_len)
{
    int retval = -1;
    ASN1_const_CTX c;
    long length = indata_len;
    int Ttag, Tclass;
    long Tlen;

    c.pp = (const unsigned char **)&indata;
    c.q = *(const unsigned char **)&indata;
    c.error = ERR_R_NESTED_ASN1_ERROR;
    c.p= *(const unsigned char **)&indata;
    c.max = (length == 0)?0:(c.p+length);

    asn1_GetSequence(&c,&length);

    ASN1_get_object(&c.p,&Tlen,&Ttag,&Tclass,c.slen);
    c.p += Tlen;
    ASN1_get_object(&c.p,&Tlen,&Ttag,&Tclass,c.slen);

    asn1_const_Finish(&c);

    *outdata = malloc((size_t)Tlen);
    if (*outdata == NULL) {
        retval = ENOMEM;
        goto cleanup;
    }
    memcpy(*outdata, c.p, (size_t)Tlen);
    *outdata_len = Tlen;

    retval = 0;
cleanup:

    return retval;
}
