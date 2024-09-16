iperf_recv(struct iperf_test *test, fd_set *read_setP)
{
    int r;
    struct iperf_stream *sp;

    SLIST_FOREACH(sp, &test->streams, streams) {
	if (FD_ISSET(sp->socket, read_setP)) {
	    if ((r = sp->rcv(sp)) < 0) {
		i_errno = IESTREAMREAD;
		return r;
	    }
	    test->bytes_sent += r;
	    ++test->blocks_sent;
	    FD_CLR(sp->socket, read_setP);
	}
    }

    return 0;
}
