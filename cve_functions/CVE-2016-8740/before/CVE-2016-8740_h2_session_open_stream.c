h2_stream *h2_session_open_stream(h2_session *session, int stream_id,
                                  int initiated_on, const h2_request *req)
{
    h2_stream * stream;
    apr_pool_t *stream_pool;
    
    apr_pool_create(&stream_pool, session->pool);
    apr_pool_tag(stream_pool, "h2_stream");
    
    stream = h2_stream_open(stream_id, stream_pool, session, 
                            initiated_on);
    nghttp2_session_set_stream_user_data(session->ngh2, stream_id, stream);
    
    if (req) {
        h2_stream_set_request(stream, req);
    }
    
    if (H2_STREAM_CLIENT_INITIATED(stream_id)) {
        if (stream_id > session->remote.emitted_max) {
            ++session->remote.emitted_count;
            session->remote.emitted_max = stream->id;
            session->local.accepted_max = stream->id;
        }
    }
    else {
        if (stream_id > session->local.emitted_max) {
            ++session->local.emitted_count;
            session->remote.emitted_max = stream->id;
        }
    }
    dispatch_event(session, H2_SESSION_EV_STREAM_OPEN, 0, NULL);
    
    return stream;
}
