static apr_status_t stream_schedule(h2_session *session,
                                    h2_stream *stream, int eos)
{
    (void)session;
    return h2_stream_schedule(stream, eos, h2_session_push_enabled(session), 
                              stream_pri_cmp, session);
}
