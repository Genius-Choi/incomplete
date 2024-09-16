http_copyheader(struct worker *w, int fd, struct http *to,
    const struct http *fm, unsigned n)
{

	CHECK_OBJ_NOTNULL(fm, HTTP_MAGIC);
	CHECK_OBJ_NOTNULL(to, HTTP_MAGIC);
	assert(n < fm->shd);
	Tcheck(fm->hd[n]);
	if (to->nhd < to->shd) {
		to->hd[to->nhd] = fm->hd[n];
		to->hdf[to->nhd] = 0;
		to->nhd++;
	} else  {
		VSC_C_main->losthdr++;
		WSLR(w, SLT_LostHeader, fd, fm->hd[n]);
	}
}
