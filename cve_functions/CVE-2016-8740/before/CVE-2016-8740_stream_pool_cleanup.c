static apr_status_t stream_pool_cleanup(void *ctx)
{
    h2_stream *stream = ctx;
    apr_status_t status;
    
    ap_assert(stream->can_be_cleaned);
    if (stream->files) {
        apr_file_t *file;
        int i;
        for (i = 0; i < stream->files->nelts; ++i) {
            file = APR_ARRAY_IDX(stream->files, i, apr_file_t*);
            status = apr_file_close(file);
            ap_log_cerror(APLOG_MARK, APLOG_TRACE3, status, stream->session->c, 
                          "h2_stream(%ld-%d): destroy, closed file %d", 
                          stream->session->id, stream->id, i);
        }
        stream->files = NULL;
    }
    return APR_SUCCESS;
}
