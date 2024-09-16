static int _c2s_router_connect(c2s_t c2s) {
    log_write(c2s->log, LOG_NOTICE, "attempting connection to router at %s, port=%d", c2s->router_ip, c2s->router_port);

    c2s->fd = mio_connect(c2s->mio, c2s->router_port, c2s->router_ip, NULL, c2s_router_mio_callback, (void *) c2s);
    if(c2s->fd == NULL) {
        if(errno == ECONNREFUSED)
            c2s_lost_router = 1;
        log_write(c2s->log, LOG_NOTICE, "connection attempt to router failed: %s (%d)", MIO_STRERROR(MIO_ERROR), MIO_ERROR);
        return 1;
    }

    c2s->router = sx_new(c2s->sx_env, c2s->fd->fd, c2s_router_sx_callback, (void *) c2s);
    sx_client_init(c2s->router, 0, NULL, NULL, NULL, "1.0");

    return 0;
}
