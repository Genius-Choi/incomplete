message_send_groupchat_subject(const char *const roomjid, const char *const subject)
{
    xmpp_ctx_t * const ctx = connection_get_ctx();
    xmpp_stanza_t *message = stanza_create_room_subject_message(ctx, roomjid, subject);

    _send_message_stanza(message);
    xmpp_stanza_release(message);
}
