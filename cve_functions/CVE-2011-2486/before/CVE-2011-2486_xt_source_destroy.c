static void xt_source_destroy(void)
{
  if (--xt_source_count < 1 && xt_source) {
	g_source_destroy(xt_source);
	xt_source = NULL;
  }
}
