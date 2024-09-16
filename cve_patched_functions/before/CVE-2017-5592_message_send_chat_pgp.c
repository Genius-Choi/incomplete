message_send_chat_pgp(const char *const barejid, const char *const msg, gboolean request_receipt)
{
    xmpp_ctx_t * const ctx = connection_get_ctx();

    char *state = chat_session_get_state(barejid);
    char *jid = chat_session_get_jid(barejid);
    char *id = create_unique_id("msg");

    xmpp_stanza_t *message = NULL;
#ifdef HAVE_LIBGPGME
    char *account_name = session_get_account_name();
    ProfAccount *account = accounts_get_account(account_name);
    if (account->pgp_keyid) {
        Jid *jidp = jid_create(jid);
        char *encrypted = p_gpg_encrypt(jidp->barejid, msg, account->pgp_keyid);
        if (encrypted) {
            message = xmpp_message_new(ctx, STANZA_TYPE_CHAT, jid, id);
            xmpp_message_set_body(message, "This message is encrypted.");
            xmpp_stanza_t *x = xmpp_stanza_new(ctx);
            xmpp_stanza_set_name(x, STANZA_NAME_X);
            xmpp_stanza_set_ns(x, STANZA_NS_ENCRYPTED);
            xmpp_stanza_t *enc_st = xmpp_stanza_new(ctx);
            xmpp_stanza_set_text(enc_st, encrypted);
            xmpp_stanza_add_child(x, enc_st);
            xmpp_stanza_release(enc_st);
            xmpp_stanza_add_child(message, x);
            xmpp_stanza_release(x);
            free(encrypted);
        } else {
            message = xmpp_message_new(ctx, STANZA_TYPE_CHAT, jid, id);
            xmpp_message_set_body(message, msg);
        }
        jid_destroy(jidp);
    } else {
        message = xmpp_message_new(ctx, STANZA_TYPE_CHAT, jid, id);
        xmpp_message_set_body(message, msg);
    }
    account_free(account);
#else
    message = xmpp_message_new(ctx, STANZA_TYPE_CHAT, jid, id);
    xmpp_message_set_body(message, msg);
#endif
    free(jid);

    if (state) {
        stanza_attach_state(ctx, message, state);
    }

    if (request_receipt) {
        stanza_attach_receipt_request(ctx, message);
    }

    _send_message_stanza(message);
    xmpp_stanza_release(message);

    return id;
}
