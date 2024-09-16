wait_for_job(conn c, int timeout)
{
    int r;

    c->state = STATE_WAIT;
    enqueue_waiting_conn(c);

    /* Set the pending timeout to the requested timeout amount */
    c->pending_timeout = timeout;

    /* this conn is waiting, but we want to know if they hang up */
    r = conn_update_evq(c, EV_READ | EV_PERSIST);
    if (r == -1) return twarnx("update events failed"), conn_close(c);
}
