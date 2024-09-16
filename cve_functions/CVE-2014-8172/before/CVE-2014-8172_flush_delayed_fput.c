void flush_delayed_fput(void)
{
	delayed_fput(NULL);
}
