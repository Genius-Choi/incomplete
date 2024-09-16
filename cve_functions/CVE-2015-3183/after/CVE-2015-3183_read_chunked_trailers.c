static apr_status_t read_chunked_trailers(http_ctx_t *ctx, ap_filter_t *f,
                                          apr_bucket_brigade *b, int merge)
{
    int rv;
    apr_bucket *e;
    request_rec *r = f->r;
    apr_table_t *saved_headers_in = r->headers_in;
    int saved_status = r->status;

    r->status = HTTP_OK;
    r->headers_in = r->trailers_in;
    apr_table_clear(r->headers_in);
    ap_get_mime_headers(r);

    if(r->status == HTTP_OK) {
        r->status = saved_status;
        e = apr_bucket_eos_create(f->c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(b, e);
        ctx->eos_sent = 1;
        rv = APR_SUCCESS;
    }
    else {
        const char *error_notes = apr_table_get(r->notes,
                                                "error-notes");
        ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(02656)
                      "Error while reading HTTP trailer: %i%s%s",
                      r->status, error_notes ? ": " : "",
                      error_notes ? error_notes : "");
        rv = APR_EINVAL;
    }

    if(!merge) {
        r->headers_in = saved_headers_in;
    }
    else {
        r->headers_in = apr_table_overlay(r->pool, saved_headers_in,
                r->trailers_in);
    }

    return rv;
}
