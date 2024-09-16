pkinit_alg_values(krb5_context context,
                  const krb5_data *alg_id,
                  size_t *hash_bytes,
                  const EVP_MD *(**func)(void))
{
    *hash_bytes = 0;
    *func = NULL;
    if ((alg_id->length == krb5_pkinit_sha1_oid_len) &&
        (0 == memcmp(alg_id->data, &krb5_pkinit_sha1_oid,
                     krb5_pkinit_sha1_oid_len))) {
        *hash_bytes = 20;
        *func = &EVP_sha1;
        return 0;
    } else if ((alg_id->length == krb5_pkinit_sha256_oid_len) &&
               (0 == memcmp(alg_id->data, krb5_pkinit_sha256_oid,
                            krb5_pkinit_sha256_oid_len))) {
        *hash_bytes = 32;
        *func = &EVP_sha256;
        return 0;
    } else if ((alg_id->length == krb5_pkinit_sha512_oid_len) &&
               (0 == memcmp(alg_id->data, krb5_pkinit_sha512_oid,
                            krb5_pkinit_sha512_oid_len))) {
        *hash_bytes = 64;
        *func = &EVP_sha512;
        return 0;
    } else {
        krb5_set_error_message(context, KRB5_ERR_BAD_S2K_PARAMS,
                               "Bad algorithm ID passed to PK-INIT KDF.");
        return KRB5_ERR_BAD_S2K_PARAMS;
    }
} /* pkinit_alg_values() */
