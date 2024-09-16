message_send_inactive(const char *const jid)
{
    xmpp_ctx_t * const ctx = connection_get_ctx();
    xmpp_stanza_t *stanza = stanza_create_chat_state(ctx, jid, STANZA_NAME_INACTIVE);

    _send_message_stanza(stanza);
    xmpp_stanza_release(stanza);
}
