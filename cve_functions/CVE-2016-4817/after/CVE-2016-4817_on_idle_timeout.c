static void on_idle_timeout(h2o_timeout_entry_t *entry)
{
    h2o_http2_conn_t *conn = H2O_STRUCT_FROM_MEMBER(h2o_http2_conn_t, _timeout_entry, entry);

    enqueue_goaway(conn, H2O_HTTP2_ERROR_NONE, h2o_iovec_init(H2O_STRLIT("idle timeout")));
    close_connection(conn);
}
