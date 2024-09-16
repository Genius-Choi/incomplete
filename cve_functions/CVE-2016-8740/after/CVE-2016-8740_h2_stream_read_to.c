apr_status_t h2_stream_read_to(h2_stream *stream, apr_bucket_brigade *bb, 
                               apr_off_t *plen, int *peos)
{
    conn_rec *c = stream->session->c;
    apr_status_t status = APR_SUCCESS;

    if (stream->rst_error) {
        return APR_ECONNRESET;
    }
    status = h2_append_brigade(bb, stream->out_buffer, plen, peos, is_not_headers);
    if (status == APR_SUCCESS && !*peos && !*plen) {
        status = APR_EAGAIN;
    }
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, c,
                  "h2_stream(%ld-%d): read_to, len=%ld eos=%d",
                  c->id, stream->id, (long)*plen, *peos);
    return status;
}
