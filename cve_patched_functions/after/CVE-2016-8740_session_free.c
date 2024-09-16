static void session_free(void *p, void *ctx)
{
    h2_session *session = ctx;

    ap_log_cerror(APLOG_MARK, APLOG_TRACE6, 0, session->c,
                  "h2_session(%ld): free()",
                  session->id);
    free(p);
}
