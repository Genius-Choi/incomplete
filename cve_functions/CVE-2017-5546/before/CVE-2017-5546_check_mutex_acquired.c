static void check_mutex_acquired(void)
{
	BUG_ON(!mutex_is_locked(&slab_mutex));
}
