static void sig_chat_protocol_deinit(CHAT_PROTOCOL_REC *proto)
{
        disconnect_servers(servers, proto->id);
        disconnect_servers(lookup_servers, proto->id);
}
