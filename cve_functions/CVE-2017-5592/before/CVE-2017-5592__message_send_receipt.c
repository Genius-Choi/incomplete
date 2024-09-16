_message_send_receipt(const char *const fulljid, const char *const message_id)
{
    xmpp_ctx_t * const ctx = connection_get_ctx();

    char *id = create_unique_id("receipt");
    xmpp_stanza_t *message = xmpp_message_new(ctx, NULL, fulljid, id);
    free(id);

    xmpp_stanza_t *receipt = xmpp_stanza_new(ctx);
    xmpp_stanza_set_name(receipt, "received");
    xmpp_stanza_set_ns(receipt, STANZA_NS_RECEIPTS);
    xmpp_stanza_set_id(receipt, message_id);

    xmpp_stanza_add_child(message, receipt);
    xmpp_stanza_release(receipt);

    _send_message_stanza(message);
    xmpp_stanza_release(message);
}
