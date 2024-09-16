pkinit_init_pkinit_oids(pkinit_plg_crypto_context ctx)
{
    ctx->id_pkinit_san = OBJ_txt2obj("1.3.6.1.5.2.2", 1);
    if (ctx->id_pkinit_san == NULL)
        return ENOMEM;

    ctx->id_pkinit_authData = OBJ_txt2obj("1.3.6.1.5.2.3.1", 1);
    if (ctx->id_pkinit_authData == NULL)
        return ENOMEM;

    ctx->id_pkinit_DHKeyData = OBJ_txt2obj("1.3.6.1.5.2.3.2", 1);
    if (ctx->id_pkinit_DHKeyData == NULL)
        return ENOMEM;

    ctx->id_pkinit_rkeyData = OBJ_txt2obj("1.3.6.1.5.2.3.3", 1);
    if (ctx->id_pkinit_rkeyData == NULL)
        return ENOMEM;

    ctx->id_pkinit_KPClientAuth = OBJ_txt2obj("1.3.6.1.5.2.3.4", 1);
    if (ctx->id_pkinit_KPClientAuth == NULL)
        return ENOMEM;

    ctx->id_pkinit_KPKdc = OBJ_txt2obj("1.3.6.1.5.2.3.5", 1);
    if (ctx->id_pkinit_KPKdc == NULL)
        return ENOMEM;

    ctx->id_ms_kp_sc_logon = OBJ_txt2obj("1.3.6.1.4.1.311.20.2.2", 1);
    if (ctx->id_ms_kp_sc_logon == NULL)
        return ENOMEM;

    ctx->id_ms_san_upn = OBJ_txt2obj("1.3.6.1.4.1.311.20.2.3", 1);
    if (ctx->id_ms_san_upn == NULL)
        return ENOMEM;

    ctx->id_kp_serverAuth = OBJ_txt2obj("1.3.6.1.5.5.7.3.1", 1);
    if (ctx->id_kp_serverAuth == NULL)
        return ENOMEM;

    return 0;
}
