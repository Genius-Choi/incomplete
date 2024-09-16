void StreamTcpSetSessionBypassFlag (TcpSession *ssn)
{
    ssn->flags |= STREAMTCP_FLAG_BYPASS;
}
