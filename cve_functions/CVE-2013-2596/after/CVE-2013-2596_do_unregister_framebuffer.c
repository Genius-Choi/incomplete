static int do_unregister_framebuffer(struct fb_info *fb_info)
{
	struct fb_event event;
	int i, ret = 0;

	i = fb_info->node;
	if (i < 0 || i >= FB_MAX || registered_fb[i] != fb_info)
		return -EINVAL;

	if (!lock_fb_info(fb_info))
		return -ENODEV;
	console_lock();
	event.info = fb_info;
	ret = fb_notifier_call_chain(FB_EVENT_FB_UNBIND, &event);
	console_unlock();
	unlock_fb_info(fb_info);

	if (ret)
		return -EINVAL;

	unlink_framebuffer(fb_info);
	if (fb_info->pixmap.addr &&
	    (fb_info->pixmap.flags & FB_PIXMAP_DEFAULT))
		kfree(fb_info->pixmap.addr);
	fb_destroy_modelist(&fb_info->modelist);
	registered_fb[i] = NULL;
	num_registered_fb--;
	fb_cleanup_device(fb_info);
	event.info = fb_info;
	console_lock();
	fb_notifier_call_chain(FB_EVENT_FB_UNREGISTERED, &event);
	console_unlock();

	/* this may free fb info */
	put_fb_info(fb_info);
	return 0;
}
