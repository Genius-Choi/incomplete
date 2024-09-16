_private_chat_handler(xmpp_stanza_t *const stanza, const char *const fulljid)
{
    char *message = xmpp_message_get_body(stanza);
    if (!message) {
        return;
    }

    GDateTime *timestamp = stanza_get_delay(stanza);
    if (timestamp) {
        sv_ev_delayed_private_message(fulljid, message, timestamp);
        g_date_time_unref(timestamp);
    } else {
        sv_ev_incoming_private_message(fulljid, message);
    }

    xmpp_ctx_t *ctx = connection_get_ctx();
    xmpp_free(ctx, message);
}
