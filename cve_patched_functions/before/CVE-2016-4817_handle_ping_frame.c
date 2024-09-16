static int handle_ping_frame(h2o_http2_conn_t *conn, h2o_http2_frame_t *frame, const char **err_desc)
{
    h2o_http2_ping_payload_t payload;
    int ret;

    if ((ret = h2o_http2_decode_ping_payload(&payload, frame, err_desc)) != 0)
        return ret;

    h2o_http2_encode_ping_frame(&conn->_write.buf, 1, payload.data);
    h2o_http2_conn_request_write(conn);

    return 0;
}
