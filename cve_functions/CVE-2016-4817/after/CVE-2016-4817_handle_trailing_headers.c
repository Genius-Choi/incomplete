static int handle_trailing_headers(h2o_http2_conn_t *conn, h2o_http2_stream_t *stream, const uint8_t *src, size_t len,
                                   const char **err_desc)
{
    size_t dummy_content_length;
    int ret;

    assert(stream->state == H2O_HTTP2_STREAM_STATE_RECV_BODY);

    if ((ret = h2o_hpack_parse_headers(&stream->req, &conn->_input_header_table, src, len, NULL, &dummy_content_length,
                                       err_desc)) != 0)
        return ret;

    execute_or_enqueue_request(conn, stream);
    return 0;
}
