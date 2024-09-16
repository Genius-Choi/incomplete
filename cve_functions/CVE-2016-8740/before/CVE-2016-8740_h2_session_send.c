static apr_status_t h2_session_send(h2_session *session)
{
    apr_interval_time_t saved_timeout;
    int rv;
    apr_socket_t *socket;
    
    socket = ap_get_conn_socket(session->c);
    if (socket) {
        apr_socket_timeout_get(socket, &saved_timeout);
        apr_socket_timeout_set(socket, session->s->timeout);
    }
    
    rv = nghttp2_session_send(session->ngh2);
    
    if (socket) {
        apr_socket_timeout_set(socket, saved_timeout);
    }
    session->have_written = 1;
    if (rv != 0) {
        if (nghttp2_is_fatal(rv)) {
            dispatch_event(session, H2_SESSION_EV_PROTO_ERROR, rv, nghttp2_strerror(rv));
            return APR_EGENERAL;
        }
    }
    
    session->unsent_promises = 0;
    session->unsent_submits = 0;
    
    return APR_SUCCESS;
}
