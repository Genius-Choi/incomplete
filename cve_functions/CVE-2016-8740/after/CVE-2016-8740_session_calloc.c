static void *session_calloc(size_t n, size_t size, void *ctx)
{
    h2_session *session = ctx;

    ap_log_cerror(APLOG_MARK, APLOG_TRACE6, 0, session->c,
                  "h2_session(%ld): calloc(%ld, %ld)",
                  session->id, (long)n, (long)size);
    return calloc(n, size);
}
