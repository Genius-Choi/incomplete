pkinit_open_session(krb5_context context,
                    pkinit_identity_crypto_context cctx)
{
    CK_ULONG i, r;
    unsigned char *cp;
    CK_ULONG count = 0;
    CK_SLOT_ID_PTR slotlist;
    CK_TOKEN_INFO tinfo;

    if (cctx->p11_module != NULL)
        return 0; /* session already open */

    /* Load module */
    cctx->p11_module =
        pkinit_C_LoadModule(cctx->p11_module_name, &cctx->p11);
    if (cctx->p11_module == NULL)
        return KRB5KDC_ERR_PREAUTH_FAILED;

    /* Init */
    if ((r = cctx->p11->C_Initialize(NULL)) != CKR_OK) {
        pkiDebug("C_Initialize: %s\n", pkinit_pkcs11_code_to_text(r));
        return KRB5KDC_ERR_PREAUTH_FAILED;
    }

    /* Get the list of available slots */
    if (cctx->slotid != PK_NOSLOT) {
        /* A slot was specified, so that's the only one in the list */
        count = 1;
        slotlist = malloc(sizeof(CK_SLOT_ID));
        slotlist[0] = cctx->slotid;
    } else {
        if (cctx->p11->C_GetSlotList(TRUE, NULL, &count) != CKR_OK)
            return KRB5KDC_ERR_PREAUTH_FAILED;
        if (count == 0)
            return KRB5KDC_ERR_PREAUTH_FAILED;
        slotlist = malloc(count * sizeof (CK_SLOT_ID));
        if (cctx->p11->C_GetSlotList(TRUE, slotlist, &count) != CKR_OK)
            return KRB5KDC_ERR_PREAUTH_FAILED;
    }

    /* Look for the given token label, or if none given take the first one */
    for (i = 0; i < count; i++) {
        /* Open session */
        if ((r = cctx->p11->C_OpenSession(slotlist[i], CKF_SERIAL_SESSION,
                                          NULL, NULL, &cctx->session)) != CKR_OK) {
            pkiDebug("C_OpenSession: %s\n", pkinit_pkcs11_code_to_text(r));
            return KRB5KDC_ERR_PREAUTH_FAILED;
        }

        /* Get token info */
        if ((r = cctx->p11->C_GetTokenInfo(slotlist[i], &tinfo)) != CKR_OK) {
            pkiDebug("C_GetTokenInfo: %s\n", pkinit_pkcs11_code_to_text(r));
            return KRB5KDC_ERR_PREAUTH_FAILED;
        }
        for (cp = tinfo.label + sizeof (tinfo.label) - 1;
             *cp == '\0' || *cp == ' '; cp--)
            *cp = '\0';
        pkiDebug("open_session: slotid %d token \"%s\"\n",
                 (int) slotlist[i], tinfo.label);
        if (cctx->token_label == NULL ||
            !strcmp((char *) cctx->token_label, (char *) tinfo.label))
            break;
        cctx->p11->C_CloseSession(cctx->session);
    }
    if (i >= count) {
        free(slotlist);
        pkiDebug("open_session: no matching token found\n");
        return KRB5KDC_ERR_PREAUTH_FAILED;
    }
    cctx->slotid = slotlist[i];
    free(slotlist);
    pkiDebug("open_session: slotid %d (%lu of %d)\n", (int) cctx->slotid,
             i + 1, (int) count);

    /* Login if needed */
    if (tinfo.flags & CKF_LOGIN_REQUIRED)
        r = pkinit_login(context, cctx, &tinfo);

    return r;
}
