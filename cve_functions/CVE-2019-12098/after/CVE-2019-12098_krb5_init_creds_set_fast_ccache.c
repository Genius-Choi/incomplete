krb5_init_creds_set_fast_ccache(krb5_context context,
				krb5_init_creds_context ctx,
				krb5_ccache fast_ccache)
{
    ctx->fast_state.armor_ccache = fast_ccache;
    ctx->fast_state.flags |= KRB5_FAST_REQUIRED;
    return 0;
}
