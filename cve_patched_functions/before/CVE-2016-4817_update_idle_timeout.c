static void update_idle_timeout(h2o_http2_conn_t *conn)
{
    h2o_timeout_unlink(&conn->_timeout_entry);

    if (conn->num_streams.pull.half_closed + conn->num_streams.push.half_closed == 0) {
        assert(h2o_linklist_is_empty(&conn->_pending_reqs));
        conn->_timeout_entry.cb = on_idle_timeout;
        h2o_timeout_link(conn->super.ctx->loop, &conn->super.ctx->http2.idle_timeout, &conn->_timeout_entry);
    }
}
