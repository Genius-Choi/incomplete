static void __exit cleanup_opl3(void)
{
	if (devc && io != -1)
	{
		if (devc->base) {
			release_region(devc->base,4);
			if (devc->is_opl4)
				release_region(devc->base - 8, 2);
		}
		kfree(devc);
		devc = NULL;
		sound_unload_synthdev(me);
	}
}
