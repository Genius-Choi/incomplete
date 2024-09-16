static int au1200fb_drv_resume(struct device *dev)
{
	struct au1200fb_platdata *pd = dev_get_drvdata(dev);
	struct fb_info *fbi;
	int i;

	/* Kickstart the panel */
	au1200_setpanel(panel, pd);

	for (i = 0; i < device_count; i++) {
		fbi = _au1200fb_infos[i];
		au1200fb_fb_set_par(fbi);
	}

	return 0;
}
