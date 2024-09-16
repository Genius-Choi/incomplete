_receipt_request_handler(xmpp_stanza_t *const stanza)
{
    if (!prefs_get_boolean(PREF_RECEIPTS_SEND)) {
        return;
    }

    const char *id = xmpp_stanza_get_id(stanza);
    if (!id) {
        return;
    }

    xmpp_stanza_t *receipts = xmpp_stanza_get_child_by_ns(stanza, STANZA_NS_RECEIPTS);
    if (!receipts) {
        return;
    }

    const char *receipts_name = xmpp_stanza_get_name(receipts);
    if (g_strcmp0(receipts_name, "request") != 0) {
        return;
    }

    const gchar *from = xmpp_stanza_get_from(stanza);
    Jid *jid = jid_create(from);
    _message_send_receipt(jid->fulljid, id);
    jid_destroy(jid);
}
