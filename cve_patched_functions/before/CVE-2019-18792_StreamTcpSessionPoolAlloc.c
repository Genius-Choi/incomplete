static void *StreamTcpSessionPoolAlloc(void)
{
    void *ptr = NULL;

    if (StreamTcpCheckMemcap((uint32_t)sizeof(TcpSession)) == 0)
        return NULL;

    ptr = SCMalloc(sizeof(TcpSession));
    if (unlikely(ptr == NULL))
        return NULL;

    return ptr;
}
