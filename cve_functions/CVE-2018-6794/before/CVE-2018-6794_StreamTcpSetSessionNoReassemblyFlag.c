void StreamTcpSetSessionNoReassemblyFlag (TcpSession *ssn, char direction)
{
    ssn->flags |= STREAMTCP_FLAG_APP_LAYER_DISABLED;
    if (direction) {
        ssn->server.flags |= STREAMTCP_STREAM_FLAG_NEW_RAW_DISABLED;
    } else {
        ssn->client.flags |= STREAMTCP_STREAM_FLAG_NEW_RAW_DISABLED;
    }
}
