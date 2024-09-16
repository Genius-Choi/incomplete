apr_status_t h2_stream_write_data(h2_stream *stream,
                                  const char *data, size_t len, int eos)
{
    conn_rec *c = stream->session->c;
    apr_status_t status = APR_SUCCESS;
    apr_bucket_brigade *tmp;
    
    ap_assert(stream);
    if (!stream->input) {
        return APR_EOF;
    }
    if (input_closed(stream) || !stream->request) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
                      "h2_stream(%ld-%d): writing denied, closed=%d, eoh=%d", 
                      stream->session->id, stream->id, input_closed(stream),
                      stream->request != NULL);
        return APR_EINVAL;
    }

    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
                  "h2_stream(%ld-%d): add %ld input bytes", 
                  stream->session->id, stream->id, (long)len);
    
    tmp = apr_brigade_create(stream->pool, c->bucket_alloc);
    apr_brigade_write(tmp, NULL, NULL, data, len);
    status = h2_beam_send(stream->input, tmp, APR_BLOCK_READ);
    apr_brigade_destroy(tmp);
    
    stream->in_data_frames++;
    stream->in_data_octets += len;
    
    if (eos) {
        return h2_stream_close_input(stream);
    }
    
    return status;
}
