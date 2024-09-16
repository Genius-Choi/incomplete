static void conn_cleanup(conn *c) {
    assert(c != NULL);

    conn_release_items(c);

    if (c->write_and_free) {
        free(c->write_and_free);
        c->write_and_free = 0;
    }

    if (c->sasl_conn) {
        assert(settings.sasl);
        sasl_dispose(&c->sasl_conn);
        c->sasl_conn = NULL;
    }

    if (IS_UDP(c->transport)) {
        conn_set_state(c, conn_read);
    }
}
