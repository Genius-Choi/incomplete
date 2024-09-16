void conn_worker_readd(conn *c) {
    c->ev_flags = EV_READ | EV_PERSIST;
    event_set(&c->event, c->sfd, c->ev_flags, event_handler, (void *)c);
    event_base_set(c->thread->base, &c->event);
    c->state = conn_new_cmd;

    if (event_add(&c->event, 0) == -1) {
        perror("event_add");
    }
}
