void h2_stream_destroy(h2_stream *stream)
{
    ap_assert(stream);
    ap_assert(!h2_mplx_stream_get(stream->session->mplx, stream->id));
    ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, stream->session->c, 
                  "h2_stream(%ld-%d): destroy", 
                  stream->session->id, stream->id);
    stream->can_be_cleaned = 1;
    if (stream->pool) {
        apr_pool_destroy(stream->pool);
    }
}
