void StreamTcpSetDisableRawReassemblyFlag (TcpSession *ssn, char direction)
{
    direction ? (ssn->server.flags |= STREAMTCP_STREAM_FLAG_NEW_RAW_DISABLED) :
                (ssn->client.flags |= STREAMTCP_STREAM_FLAG_NEW_RAW_DISABLED);
}
