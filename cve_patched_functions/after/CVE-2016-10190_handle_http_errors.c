static void handle_http_errors(URLContext *h, int error)
{
    av_assert0(error < 0);
    http_write_reply(h, error);
}
