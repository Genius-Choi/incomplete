message_send_chat_otr(const char *const barejid, const char *const msg, gboolean request_receipt)
{
    xmpp_ctx_t * const ctx = connection_get_ctx();

    char *state = chat_session_get_state(barejid);
    char *jid = chat_session_get_jid(barejid);
    char *id = create_unique_id("msg");

    xmpp_stanza_t *message = xmpp_message_new(ctx, STANZA_TYPE_CHAT, barejid, id);
    xmpp_message_set_body(message, msg);

    free(jid);

    if (state) {
        stanza_attach_state(ctx, message, state);
    }

    stanza_attach_carbons_private(ctx, message);
    stanza_attach_hints_no_copy(ctx, message);
    stanza_attach_hints_no_store(ctx, message);

    if (request_receipt) {
        stanza_attach_receipt_request(ctx, message);
    }

    _send_message_stanza(message);
    xmpp_stanza_release(message);

    return id;
}
