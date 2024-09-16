chkNMIDBuffer(Buffer *buf)
{
    static char *url_like_pat[] = {
	"<[!-;=?-~]+@[a-zA-Z0-9\\.\\-_]+>",
	NULL,
    };
    int i;
    for (i = 0; url_like_pat[i]; i++) {
	reAnchorNews(buf, url_like_pat[i]);
    }
    buf->check_url |= CHK_NMID;
}
