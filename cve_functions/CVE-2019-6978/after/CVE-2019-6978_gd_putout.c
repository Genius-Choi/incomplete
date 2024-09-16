void gd_putout (int i, void *out)
{
	gdPutC(i, (gdIOCtx *) out);
}
