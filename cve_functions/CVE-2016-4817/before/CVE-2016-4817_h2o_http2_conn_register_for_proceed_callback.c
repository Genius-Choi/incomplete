void h2o_http2_conn_register_for_proceed_callback(h2o_http2_conn_t *conn, h2o_http2_stream_t *stream)
{
    h2o_http2_conn_request_write(conn);

    if (h2o_http2_stream_has_pending_data(stream) || stream->state >= H2O_HTTP2_STREAM_STATE_SEND_BODY_IS_FINAL) {
        if (h2o_http2_window_get_window(&stream->output_window) > 0) {
            assert(!h2o_linklist_is_linked(&stream->_refs.link));
            h2o_http2_scheduler_activate(&stream->_refs.scheduler);
        }
    } else {
        h2o_linklist_insert(&conn->_write.streams_to_proceed, &stream->_refs.link);
    }
}
