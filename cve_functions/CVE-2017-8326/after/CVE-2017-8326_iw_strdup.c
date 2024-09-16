IW_IMPL(char*) iw_strdup(struct iw_context *ctx, const char *s)
{
	size_t len;
	char *s2;
	if(!s) return NULL;
	len = strlen(s);
	s2 = iw_malloc(ctx, len+1);
	if(!s2) return NULL;
	memcpy(s2, s, len+1);
	return s2;
}
