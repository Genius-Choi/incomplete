http_SetHeader(struct worker *w, int fd, struct http *to, const char *hdr)
{

	CHECK_OBJ_NOTNULL(to, HTTP_MAGIC);
	if (to->nhd >= to->shd) {
		VSC_C_main->losthdr++;
		WSL(w, SLT_LostHeader, fd, "%s", hdr);
		return;
	}
	http_SetH(to, to->nhd++, hdr);
}
