message_send_groupchat(const char *const roomjid, const char *const msg, const char *const oob_url)
{
    xmpp_ctx_t * const ctx = connection_get_ctx();
    char *id = create_unique_id("muc");

    xmpp_stanza_t *message = xmpp_message_new(ctx, STANZA_TYPE_GROUPCHAT, roomjid, id);
    xmpp_message_set_body(message, msg);

    free(id);

    if (oob_url) {
        stanza_attach_x_oob_url(ctx, message, oob_url);
    }

    _send_message_stanza(message);
    xmpp_stanza_release(message);
}
