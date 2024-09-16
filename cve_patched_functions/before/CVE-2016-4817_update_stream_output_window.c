static int update_stream_output_window(h2o_http2_stream_t *stream, ssize_t delta)
{
    ssize_t cur = h2o_http2_window_get_window(&stream->output_window);
    if (h2o_http2_window_update(&stream->output_window, delta) != 0)
        return -1;
    if (cur <= 0 && h2o_http2_window_get_window(&stream->output_window) > 0 && h2o_http2_stream_has_pending_data(stream)) {
        assert(!h2o_linklist_is_linked(&stream->_refs.link));
        h2o_http2_scheduler_activate(&stream->_refs.scheduler);
    }
    return 0;
}
