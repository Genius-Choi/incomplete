static apr_status_t on_stream_resume(void *ctx, h2_stream *stream)
{
    h2_session *session = ctx;
    apr_status_t status = APR_EAGAIN;
    int rv;
    apr_off_t len = 0;
    int eos = 0;
    h2_headers *headers;
    
    ap_assert(stream);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c, 
                  "h2_stream(%ld-%d): on_resume", session->id, stream->id);
        
send_headers:
    headers = NULL;
    status = h2_stream_out_prepare(stream, &len, &eos, &headers);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, session->c, 
                  "h2_stream(%ld-%d): prepared len=%ld, eos=%d", 
                  session->id, stream->id, (long)len, eos);
    if (headers) {
        status = on_stream_headers(session, stream, headers, len, eos);
        if (status != APR_SUCCESS || stream->rst_error) {
            return status;
        }
        goto send_headers;
    }
    else if (status != APR_EAGAIN) {
        if (!stream->has_response) {
            int err = H2_STREAM_RST(stream, H2_ERR_PROTOCOL_ERROR);
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03466)
                          "h2_stream(%ld-%d): no response, RST_STREAM, err=%d",
                          session->id, stream->id, err);
            nghttp2_submit_rst_stream(session->ngh2, NGHTTP2_FLAG_NONE,
                                      stream->id, err);
            return APR_SUCCESS;
        } 
        rv = nghttp2_session_resume_data(session->ngh2, stream->id);
        session->have_written = 1;
        ap_log_cerror(APLOG_MARK, nghttp2_is_fatal(rv)?
                      APLOG_ERR : APLOG_DEBUG, 0, session->c,
                      APLOGNO(02936) 
                      "h2_stream(%ld-%d): resuming %s",
                      session->id, stream->id, rv? nghttp2_strerror(rv) : "");
    }
    return status;
}
