void h2o_http2_conn_unregister_stream(h2o_http2_conn_t *conn, h2o_http2_stream_t *stream)
{
    khiter_t iter = kh_get(h2o_http2_stream_t, conn->streams, stream->stream_id);
    assert(iter != kh_end(conn->streams));
    kh_del(h2o_http2_stream_t, conn->streams, iter);

    assert(h2o_http2_scheduler_is_open(&stream->_refs.scheduler));
    h2o_http2_scheduler_close(&stream->_refs.scheduler);

    switch (stream->state) {
    case H2O_HTTP2_STREAM_STATE_IDLE:
    case H2O_HTTP2_STREAM_STATE_RECV_HEADERS:
    case H2O_HTTP2_STREAM_STATE_RECV_BODY:
        assert(!h2o_linklist_is_linked(&stream->_refs.link));
        break;
    case H2O_HTTP2_STREAM_STATE_REQ_PENDING:
        assert(h2o_linklist_is_linked(&stream->_refs.link));
        h2o_linklist_unlink(&stream->_refs.link);
        break;
    case H2O_HTTP2_STREAM_STATE_SEND_HEADERS:
    case H2O_HTTP2_STREAM_STATE_SEND_BODY:
    case H2O_HTTP2_STREAM_STATE_SEND_BODY_IS_FINAL:
    case H2O_HTTP2_STREAM_STATE_END_STREAM:
        if (h2o_linklist_is_linked(&stream->_refs.link))
            h2o_linklist_unlink(&stream->_refs.link);
        break;
    }
    if (stream->state != H2O_HTTP2_STREAM_STATE_END_STREAM)
        h2o_http2_stream_set_state(conn, stream, H2O_HTTP2_STREAM_STATE_END_STREAM);

    if (conn->state < H2O_HTTP2_CONN_STATE_IS_CLOSING) {
        run_pending_requests(conn);
        update_idle_timeout(conn);
    }
}
