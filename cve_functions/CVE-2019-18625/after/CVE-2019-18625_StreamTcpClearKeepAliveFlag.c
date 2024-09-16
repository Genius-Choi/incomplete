static void StreamTcpClearKeepAliveFlag(TcpSession *ssn, Packet *p)
{
    TcpStream *stream = NULL;

    if (p->flags & PKT_PSEUDO_STREAM_END)
        return;

    if (PKT_IS_TOSERVER(p)) {
        stream = &ssn->client;
    } else {
        stream = &ssn->server;
    }

    if (stream->flags & STREAMTCP_STREAM_FLAG_KEEPALIVE) {
        stream->flags &= ~STREAMTCP_STREAM_FLAG_KEEPALIVE;
        SCLogDebug("FLAG_KEEPALIVE cleared");
    }
}
