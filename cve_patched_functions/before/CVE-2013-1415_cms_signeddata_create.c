cms_signeddata_create(krb5_context context,
                      pkinit_plg_crypto_context plg_cryptoctx,
                      pkinit_req_crypto_context req_cryptoctx,
                      pkinit_identity_crypto_context id_cryptoctx,
                      int cms_msg_type,
                      int include_certchain,
                      unsigned char *data,
                      unsigned int data_len,
                      unsigned char **signed_data,
                      unsigned int *signed_data_len)
{
    krb5_error_code retval = ENOMEM;
    PKCS7  *p7 = NULL, *inner_p7 = NULL;
    PKCS7_SIGNED *p7s = NULL;
    PKCS7_SIGNER_INFO *p7si = NULL;
    unsigned char *p;
    STACK_OF(X509) * cert_stack = NULL;
    ASN1_OCTET_STRING *digest_attr = NULL;
    EVP_MD_CTX ctx, ctx2;
    const EVP_MD *md_tmp = NULL;
    unsigned char md_data[EVP_MAX_MD_SIZE], md_data2[EVP_MAX_MD_SIZE];
    unsigned char *digestInfo_buf = NULL, *abuf = NULL;
    unsigned int md_len, md_len2, alen, digestInfo_len;
    STACK_OF(X509_ATTRIBUTE) * sk;
    unsigned char *sig = NULL;
    unsigned int sig_len = 0;
    X509_ALGOR *alg = NULL;
    ASN1_OCTET_STRING *digest = NULL;
    unsigned int alg_len = 0, digest_len = 0;
    unsigned char *y = NULL, *alg_buf = NULL, *digest_buf = NULL;
    X509 *cert = NULL;
    ASN1_OBJECT *oid = NULL;

    /* Start creating PKCS7 data. */
    if ((p7 = PKCS7_new()) == NULL)
        goto cleanup;
    p7->type = OBJ_nid2obj(NID_pkcs7_signed);

    if ((p7s = PKCS7_SIGNED_new()) == NULL)
        goto cleanup;
    p7->d.sign = p7s;
    if (!ASN1_INTEGER_set(p7s->version, 3))
        goto cleanup;

    /* pick the correct oid for the eContentInfo */
    oid = pkinit_pkcs7type2oid(plg_cryptoctx, cms_msg_type);
    if (oid == NULL)
        goto cleanup;

    if (id_cryptoctx->my_certs != NULL) {
        /* create a cert chain that has at least the signer's certificate */
        if ((cert_stack = sk_X509_new_null()) == NULL)
            goto cleanup;

        cert = sk_X509_value(id_cryptoctx->my_certs, id_cryptoctx->cert_index);
        if (!include_certchain) {
            pkiDebug("only including signer's certificate\n");
            sk_X509_push(cert_stack, X509_dup(cert));
        } else {
            /* create a cert chain */
            X509_STORE *certstore = NULL;
            X509_STORE_CTX certctx;
            STACK_OF(X509) *certstack = NULL;
            char buf[DN_BUF_LEN];
            unsigned int i = 0, size = 0;

            if ((certstore = X509_STORE_new()) == NULL)
                goto cleanup;
            pkiDebug("building certificate chain\n");
            X509_STORE_set_verify_cb_func(certstore, openssl_callback);
            X509_STORE_CTX_init(&certctx, certstore, cert,
                                id_cryptoctx->intermediateCAs);
            X509_STORE_CTX_trusted_stack(&certctx, id_cryptoctx->trustedCAs);
            if (!X509_verify_cert(&certctx)) {
                int code = X509_STORE_CTX_get_error(&certctx);
                const char *msg = X509_verify_cert_error_string(code);
                pkiDebug("failed to create a certificate chain: %s\n", msg);
                if (!sk_X509_num(id_cryptoctx->trustedCAs))
                    pkiDebug("No trusted CAs found. Check your X509_anchors\n");
                retval = KRB5_PREAUTH_FAILED;
                krb5_set_error_message(context, retval,
                                       _("Cannot create cert chain: %s"), msg);
                goto cleanup;
            }
            certstack = X509_STORE_CTX_get1_chain(&certctx);
            size = sk_X509_num(certstack);
            pkiDebug("size of certificate chain = %d\n", size);
            for(i = 0; i < size - 1; i++) {
                X509 *x = sk_X509_value(certstack, i);
                X509_NAME_oneline(X509_get_subject_name(x), buf, sizeof(buf));
                pkiDebug("cert #%d: %s\n", i, buf);
                sk_X509_push(cert_stack, X509_dup(x));
            }
            X509_STORE_CTX_cleanup(&certctx);
            X509_STORE_free(certstore);
            sk_X509_pop_free(certstack, X509_free);
        }
        p7s->cert = cert_stack;

        /* fill-in PKCS7_SIGNER_INFO */
        if ((p7si = PKCS7_SIGNER_INFO_new()) == NULL)
            goto cleanup;
        if (!ASN1_INTEGER_set(p7si->version, 1))
            goto cleanup;
        if (!X509_NAME_set(&p7si->issuer_and_serial->issuer,
                           X509_get_issuer_name(cert)))
            goto cleanup;
        /* because ASN1_INTEGER_set is used to set a 'long' we will do
         * things the ugly way. */
        M_ASN1_INTEGER_free(p7si->issuer_and_serial->serial);
        if (!(p7si->issuer_and_serial->serial =
              M_ASN1_INTEGER_dup(X509_get_serialNumber(cert))))
            goto cleanup;

        /* will not fill-out EVP_PKEY because it's on the smartcard */

        /* Set digest algs */
        p7si->digest_alg->algorithm = OBJ_nid2obj(NID_sha1);

        if (p7si->digest_alg->parameter != NULL)
            ASN1_TYPE_free(p7si->digest_alg->parameter);
        if ((p7si->digest_alg->parameter = ASN1_TYPE_new()) == NULL)
            goto cleanup;
        p7si->digest_alg->parameter->type = V_ASN1_NULL;

        /* Set sig algs */
        if (p7si->digest_enc_alg->parameter != NULL)
            ASN1_TYPE_free(p7si->digest_enc_alg->parameter);
        p7si->digest_enc_alg->algorithm = OBJ_nid2obj(NID_sha1WithRSAEncryption);
        if (!(p7si->digest_enc_alg->parameter = ASN1_TYPE_new()))
            goto cleanup;
        p7si->digest_enc_alg->parameter->type = V_ASN1_NULL;

        if (cms_msg_type == CMS_SIGN_DRAFT9){
            /* don't include signed attributes for pa-type 15 request */
            abuf = data;
            alen = data_len;
        } else {
            /* add signed attributes */
            /* compute sha1 digest over the EncapsulatedContentInfo */
            EVP_MD_CTX_init(&ctx);
            EVP_DigestInit_ex(&ctx, EVP_sha1(), NULL);
            EVP_DigestUpdate(&ctx, data, data_len);
            md_tmp = EVP_MD_CTX_md(&ctx);
            EVP_DigestFinal_ex(&ctx, md_data, &md_len);

            /* create a message digest attr */
            digest_attr = ASN1_OCTET_STRING_new();
            ASN1_OCTET_STRING_set(digest_attr, md_data, (int)md_len);
            PKCS7_add_signed_attribute(p7si, NID_pkcs9_messageDigest,
                                       V_ASN1_OCTET_STRING, (char *) digest_attr);

            /* create a content-type attr */
            PKCS7_add_signed_attribute(p7si, NID_pkcs9_contentType,
                                       V_ASN1_OBJECT, oid);

            /* create the signature over signed attributes. get DER encoded value */
            /* This is the place where smartcard signature needs to be calculated */
            sk = p7si->auth_attr;
            alen = ASN1_item_i2d((ASN1_VALUE *) sk, &abuf,
                                 ASN1_ITEM_rptr(PKCS7_ATTR_SIGN));
            if (abuf == NULL)
                goto cleanup2;
        } /* signed attributes */

#ifndef WITHOUT_PKCS11
        /* Some tokens can only do RSAEncryption without sha1 hash */
        /* to compute sha1WithRSAEncryption, encode the algorithm ID for the hash
         * function and the hash value into an ASN.1 value of type DigestInfo
         * DigestInfo::=SEQUENCE {
         *  digestAlgorithm  AlgorithmIdentifier,
         *  digest OCTET STRING }
         */
        if (id_cryptoctx->pkcs11_method == 1 &&
            id_cryptoctx->mech == CKM_RSA_PKCS) {
            pkiDebug("mech = CKM_RSA_PKCS\n");
            EVP_MD_CTX_init(&ctx2);
            /* if this is not draft9 request, include digest signed attribute */
            if (cms_msg_type != CMS_SIGN_DRAFT9)
                EVP_DigestInit_ex(&ctx2, md_tmp, NULL);
            else
                EVP_DigestInit_ex(&ctx2, EVP_sha1(), NULL);
            EVP_DigestUpdate(&ctx2, abuf, alen);
            EVP_DigestFinal_ex(&ctx2, md_data2, &md_len2);

            alg = X509_ALGOR_new();
            if (alg == NULL)
                goto cleanup2;
            alg->algorithm = OBJ_nid2obj(NID_sha1);
            alg->parameter = NULL;
            alg_len = i2d_X509_ALGOR(alg, NULL);
            alg_buf = malloc(alg_len);
            if (alg_buf == NULL)
                goto cleanup2;

            digest = ASN1_OCTET_STRING_new();
            if (digest == NULL)
                goto cleanup2;
            ASN1_OCTET_STRING_set(digest, md_data2, (int)md_len2);
            digest_len = i2d_ASN1_OCTET_STRING(digest, NULL);
            digest_buf = malloc(digest_len);
            if (digest_buf == NULL)
                goto cleanup2;

            digestInfo_len = ASN1_object_size(1, (int)(alg_len + digest_len),
                                              V_ASN1_SEQUENCE);
            y = digestInfo_buf = malloc(digestInfo_len);
            if (digestInfo_buf == NULL)
                goto cleanup2;
            ASN1_put_object(&y, 1, (int)(alg_len + digest_len), V_ASN1_SEQUENCE,
                            V_ASN1_UNIVERSAL);
            i2d_X509_ALGOR(alg, &y);
            i2d_ASN1_OCTET_STRING(digest, &y);
#ifdef DEBUG_SIG
            pkiDebug("signing buffer\n");
            print_buffer(digestInfo_buf, digestInfo_len);
            print_buffer_bin(digestInfo_buf, digestInfo_len, "/tmp/pkcs7_tosign");
#endif
            retval = pkinit_sign_data(context, id_cryptoctx, digestInfo_buf,
                                      digestInfo_len, &sig, &sig_len);
        } else
#endif
        {
            pkiDebug("mech = %s\n",
                     id_cryptoctx->pkcs11_method == 1 ? "CKM_SHA1_RSA_PKCS" : "FS");
            retval = pkinit_sign_data(context, id_cryptoctx, abuf, alen,
                                      &sig, &sig_len);
        }
#ifdef DEBUG_SIG
        print_buffer(sig, sig_len);
#endif
        if (cms_msg_type != CMS_SIGN_DRAFT9 )
            free(abuf);
        if (retval)
            goto cleanup2;

        /* Add signature */
        if (!ASN1_STRING_set(p7si->enc_digest, (unsigned char *) sig,
                             (int)sig_len)) {
            unsigned long err = ERR_peek_error();
            retval = KRB5KDC_ERR_PREAUTH_FAILED;
            krb5_set_error_message(context, retval, "%s\n",
                                   ERR_error_string(err, NULL));
            pkiDebug("failed to add a signed digest attribute\n");
            goto cleanup2;
        }
        /* adder signer_info to pkcs7 signed */
        if (!PKCS7_add_signer(p7, p7si))
            goto cleanup2;
    } /* we have a certificate */

    /* start on adding data to the pkcs7 signed */
    retval = create_contentinfo(context, plg_cryptoctx, oid,
                                data, data_len, &inner_p7);
    if (p7s->contents != NULL)
        PKCS7_free(p7s->contents);
    p7s->contents = inner_p7;

    *signed_data_len = i2d_PKCS7(p7, NULL);
    if (!(*signed_data_len)) {
        unsigned long err = ERR_peek_error();
        retval = KRB5KDC_ERR_PREAUTH_FAILED;
        krb5_set_error_message(context, retval, "%s\n",
                               ERR_error_string(err, NULL));
        pkiDebug("failed to der encode pkcs7\n");
        goto cleanup2;
    }
    retval = ENOMEM;
    if ((p = *signed_data = malloc(*signed_data_len)) == NULL)
        goto cleanup2;

    /* DER encode PKCS7 data */
    retval = i2d_PKCS7(p7, &p);
    if (!retval) {
        unsigned long err = ERR_peek_error();
        retval = KRB5KDC_ERR_PREAUTH_FAILED;
        krb5_set_error_message(context, retval, "%s\n",
                               ERR_error_string(err, NULL));
        pkiDebug("failed to der encode pkcs7\n");
        goto cleanup2;
    }
    retval = 0;

#ifdef DEBUG_ASN1
    if (cms_msg_type == CMS_SIGN_CLIENT) {
        print_buffer_bin(*signed_data, *signed_data_len,
                         "/tmp/client_pkcs7_signeddata");
    } else {
        if (cms_msg_type == CMS_SIGN_SERVER) {
            print_buffer_bin(*signed_data, *signed_data_len,
                             "/tmp/kdc_pkcs7_signeddata");
        } else {
            print_buffer_bin(*signed_data, *signed_data_len,
                             "/tmp/draft9_pkcs7_signeddata");
        }
    }
#endif

cleanup2:
    if (p7si) {
        if (cms_msg_type != CMS_SIGN_DRAFT9)
            EVP_MD_CTX_cleanup(&ctx);
#ifndef WITHOUT_PKCS11
        if (id_cryptoctx->pkcs11_method == 1 &&
            id_cryptoctx->mech == CKM_RSA_PKCS) {
            EVP_MD_CTX_cleanup(&ctx2);
            free(digest_buf);
            free(digestInfo_buf);
            free(alg_buf);
            if (digest != NULL)
                ASN1_OCTET_STRING_free(digest);
        }
#endif
        if (alg != NULL)
            X509_ALGOR_free(alg);
    }
cleanup:
    if (p7 != NULL)
        PKCS7_free(p7);
    free(sig);

    return retval;
}
