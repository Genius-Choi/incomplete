apr_status_t h2_stream_set_request_rec(h2_stream *stream, request_rec *r)
{
    h2_request *req;
    apr_status_t status;

    ap_assert(stream->request == NULL);
    ap_assert(stream->rtmp == NULL);
    if (stream->rst_error) {
        return APR_ECONNRESET;
    }
    status = h2_request_rcreate(&req, stream->pool, r);
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, r, APLOGNO(03058)
                  "h2_request(%d): set_request_rec %s host=%s://%s%s",
                  stream->id, req->method, req->scheme, req->authority, 
                  req->path);
    stream->rtmp = req;
    return status;
}
