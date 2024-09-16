apr_status_t h2_stream_set_error(h2_stream *stream, int http_status)
{
    h2_headers *response;
    
    if (h2_stream_is_ready(stream)) {
        return APR_EINVAL;
    }
    if (stream->rtmp) {
        stream->request = stream->rtmp;
        stream->rtmp = NULL;
    }
    response = h2_headers_die(http_status, stream->request, stream->pool);
    prepend_response(stream, response);
    h2_beam_close(stream->output);
    return APR_SUCCESS;
}
