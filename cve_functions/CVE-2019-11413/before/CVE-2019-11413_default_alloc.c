static void *default_alloc(void *ctx, void *p, int n)
{
	return realloc(p, (size_t)n);
}
