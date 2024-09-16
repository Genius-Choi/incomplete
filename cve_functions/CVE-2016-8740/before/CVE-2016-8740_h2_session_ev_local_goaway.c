static void h2_session_ev_local_goaway(h2_session *session, int arg, const char *msg)
{
    cleanup_streams(session);
    if (!session->remote.shutdown) {
        update_child_status(session, SERVER_CLOSING, "local goaway");
    }
    transit(session, "local goaway", H2_SESSION_ST_DONE);
}
