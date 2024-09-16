static void h2_session_ev_remote_goaway(h2_session *session, int arg, const char *msg)
{
    if (!session->remote.shutdown) {
        session->remote.error = arg;
        session->remote.accepting = 0;
        session->remote.shutdown = 1;
        cleanup_streams(session);
        update_child_status(session, SERVER_CLOSING, "remote goaway");
        transit(session, "remote goaway", H2_SESSION_ST_DONE);
    }
}
