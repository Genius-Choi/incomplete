static void *session_malloc(size_t size, void *ctx)
{
    h2_session *session = ctx;
    ap_log_cerror(APLOG_MARK, APLOG_TRACE6, 0, session->c,
                  "h2_session(%ld): malloc(%ld)",
                  session->id, (long)size);
    return malloc(size);
}
