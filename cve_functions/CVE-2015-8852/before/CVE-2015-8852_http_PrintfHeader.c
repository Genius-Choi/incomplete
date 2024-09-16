http_PrintfHeader(struct worker *w, int fd, struct http *to,
    const char *fmt, ...)
{
	va_list ap;
	unsigned l, n;

	CHECK_OBJ_NOTNULL(to, HTTP_MAGIC);
	l = WS_Reserve(to->ws, 0);
	va_start(ap, fmt);
	n = vsnprintf(to->ws->f, l, fmt, ap);
	va_end(ap);
	if (n + 1 >= l || to->nhd >= to->shd) {
		VSC_C_main->losthdr++;
		WSL(w, SLT_LostHeader, fd, "%s", to->ws->f);
		WS_Release(to->ws, 0);
	} else {
		to->hd[to->nhd].b = to->ws->f;
		to->hd[to->nhd].e = to->ws->f + n;
		to->hdf[to->nhd] = 0;
		WS_Release(to->ws, n + 1);
		to->nhd++;
	}
}
