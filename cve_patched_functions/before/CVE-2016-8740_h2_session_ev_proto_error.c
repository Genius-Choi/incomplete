static void h2_session_ev_proto_error(h2_session *session, int arg, const char *msg)
{
    if (!session->local.shutdown) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03402)
                      "h2_session(%ld): proto error -> shutdown", session->id);
        h2_session_shutdown(session, arg, msg, 0);
    }
}
