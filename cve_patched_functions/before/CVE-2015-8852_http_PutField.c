http_PutField(struct worker *w, int fd, const struct http *to, int field,
    const char *string)
{
	char *p;
	unsigned l;

	CHECK_OBJ_NOTNULL(to, HTTP_MAGIC);
	l = strlen(string);
	p = WS_Alloc(to->ws, l + 1);
	if (p == NULL) {
		WSL(w, SLT_LostHeader, fd, "%s", string);
		to->hd[field].b = NULL;
		to->hd[field].e = NULL;
		to->hdf[field] = 0;
	} else {
		memcpy(p, string, l + 1L);
		to->hd[field].b = p;
		to->hd[field].e = p + l;
		to->hdf[field] = 0;
	}
}
