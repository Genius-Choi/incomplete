apr_status_t h2_session_stream_done(h2_session *session, h2_stream *stream)
{
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                  "h2_stream(%ld-%d): EOS bucket cleanup -> done", 
                  session->id, stream->id);
    h2_mplx_stream_done(session->mplx, stream);
    
    dispatch_event(session, H2_SESSION_EV_STREAM_DONE, 0, NULL);
    return APR_SUCCESS;
}
