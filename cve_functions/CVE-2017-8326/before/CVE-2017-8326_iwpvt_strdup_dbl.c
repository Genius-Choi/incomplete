char* iwpvt_strdup_dbl(struct iw_context *ctx, double n)
{
	char buf[100];
	iw_snprintf(buf, sizeof(buf), "%.20f", n);
	return iw_strdup(ctx, buf);
}
