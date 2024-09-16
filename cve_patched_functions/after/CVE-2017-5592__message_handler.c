_message_handler(xmpp_conn_t *const conn, xmpp_stanza_t *const stanza, void *const userdata)
{
    log_debug("Message stanza handler fired");

    char *text;
    size_t text_size;
    xmpp_stanza_to_text(stanza, &text, &text_size);
    gboolean cont = plugins_on_message_stanza_receive(text);
    xmpp_free(connection_get_ctx(), text);
    if (!cont) {
        return 1;
    }

    const char *type = xmpp_stanza_get_type(stanza);

    if (g_strcmp0(type, STANZA_TYPE_ERROR) == 0) {
        _handle_error(stanza);
    }

    if (g_strcmp0(type, STANZA_TYPE_GROUPCHAT) == 0) {
        _handle_groupchat(stanza);
    }

    xmpp_stanza_t *mucuser = xmpp_stanza_get_child_by_ns(stanza, STANZA_NS_MUC_USER);
    if (mucuser) {
        _handel_muc_user(stanza);
    }

    xmpp_stanza_t *conference = xmpp_stanza_get_child_by_ns(stanza, STANZA_NS_CONFERENCE);
    if (conference) {
        _handle_conference(stanza);
    }

    xmpp_stanza_t *captcha = xmpp_stanza_get_child_by_ns(stanza, STANZA_NS_CAPTCHA);
    if (captcha) {
        _handle_captcha(stanza);
    }

    xmpp_stanza_t *receipts = xmpp_stanza_get_child_by_ns(stanza, STANZA_NS_RECEIPTS);
    if (receipts) {
        _handle_receipt_received(stanza);
    }

    _handle_chat(stanza);

    return 1;
}
