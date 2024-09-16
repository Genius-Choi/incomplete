void oz_hcd_term(void)
{
	msleep(OZ_HUB_DEBOUNCE_TIMEOUT);
	tasklet_kill(&g_urb_process_tasklet);
	tasklet_kill(&g_urb_cancel_tasklet);
	platform_device_unregister(g_plat_dev);
	platform_driver_unregister(&g_oz_plat_drv);
	oz_dbg(ON, "Pending urbs:%d\n", atomic_read(&g_pending_urbs));
	kmem_cache_destroy(oz_urb_link_cache);
}
