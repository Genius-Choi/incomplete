static int StreamTcpSessionPoolInit(void *data, void* initdata)
{
    memset(data, 0, sizeof(TcpSession));
    StreamTcpIncrMemuse((uint64_t)sizeof(TcpSession));

    return 1;
}
