ar6000_alloc_netbufs(A_NETBUF_QUEUE_T *q, u16 num)
{
    void * osbuf;

    while(num) {
        if((osbuf = A_NETBUF_ALLOC(AR6000_BUFFER_SIZE))) {
            A_NETBUF_ENQUEUE(q, osbuf);
        } else {
            break;
        }
        num--;
    }

    if(num) {
        A_PRINTF("%s(), allocation of netbuf failed", __func__);
    }
}
