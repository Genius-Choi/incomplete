h2_stream *h2_stream_open(int id, apr_pool_t *pool, h2_session *session,
                          int initiated_on)
{
    h2_stream *stream = apr_pcalloc(pool, sizeof(h2_stream));
    
    stream->id           = id;
    stream->initiated_on = initiated_on;
    stream->created      = apr_time_now();
    stream->state        = H2_STREAM_ST_IDLE;
    stream->pool         = pool;
    stream->session      = session;
    stream->can_be_cleaned = 1;

    h2_beam_create(&stream->input, pool, id, "input", H2_BEAM_OWNER_SEND, 0);
    h2_beam_create(&stream->output, pool, id, "output", H2_BEAM_OWNER_RECV, 0);
    
    set_state(stream, H2_STREAM_ST_OPEN);
    apr_pool_cleanup_register(pool, stream, stream_pool_cleanup, 
                              apr_pool_cleanup_null);
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03082)
                  "h2_stream(%ld-%d): opened", session->id, stream->id);
    return stream;
}
