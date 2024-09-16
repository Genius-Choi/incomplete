pkinit_pkcs7type2oid(pkinit_plg_crypto_context cryptoctx, int pkcs7_type)
{
    int nid;

    switch (pkcs7_type) {
    case CMS_SIGN_CLIENT:
        return cryptoctx->id_pkinit_authData;
    case CMS_SIGN_DRAFT9:
        /*
         * Delay creating this OID until we know we need it.
         * It shadows an existing OpenSSL oid.  If it
         * is created too early, it breaks things like
         * the use of pkcs12 (which uses pkcs7 structures).
         * We need this shadow version because our code
         * depends on the "other" type to be unknown to the
         * OpenSSL code.
         */
        if (cryptoctx->id_pkinit_authData9 == NULL) {
            pkiDebug("%s: Creating shadow instance of pkcs7-data oid\n",
                     __FUNCTION__);
            nid = OBJ_create("1.2.840.113549.1.7.1", "id-pkcs7-data",
                             "PKCS7 data");
            if (nid == NID_undef)
                return NULL;
            cryptoctx->id_pkinit_authData9 = OBJ_nid2obj(nid);
        }
        return cryptoctx->id_pkinit_authData9;
    case CMS_SIGN_SERVER:
        return cryptoctx->id_pkinit_DHKeyData;
    case CMS_ENVEL_SERVER:
        return cryptoctx->id_pkinit_rkeyData;
    default:
        return NULL;
    }

}
