WSLH(struct worker *w, int fd, const struct http *hp, unsigned hdr)
{

	WSLR(w, http2shmlog(hp, hdr), fd, hp->hd[hdr]);
}
