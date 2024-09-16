fb_set_var(struct fb_info *info, struct fb_var_screeninfo *var)
{
	int flags = info->flags;
	int ret = 0;

	if (var->activate & FB_ACTIVATE_INV_MODE) {
		struct fb_videomode mode1, mode2;

		fb_var_to_videomode(&mode1, var);
		fb_var_to_videomode(&mode2, &info->var);
		/* make sure we don't delete the videomode of current var */
		ret = fb_mode_is_equal(&mode1, &mode2);

		if (!ret) {
		    struct fb_event event;

		    event.info = info;
		    event.data = &mode1;
		    ret = fb_notifier_call_chain(FB_EVENT_MODE_DELETE, &event);
		}

		if (!ret)
		    fb_delete_videomode(&mode1, &info->modelist);


		ret = (ret) ? -EINVAL : 0;
		goto done;
	}

	if ((var->activate & FB_ACTIVATE_FORCE) ||
	    memcmp(&info->var, var, sizeof(struct fb_var_screeninfo))) {
		u32 activate = var->activate;

		/* When using FOURCC mode, make sure the red, green, blue and
		 * transp fields are set to 0.
		 */
		if ((info->fix.capabilities & FB_CAP_FOURCC) &&
		    var->grayscale > 1) {
			if (var->red.offset     || var->green.offset    ||
			    var->blue.offset    || var->transp.offset   ||
			    var->red.length     || var->green.length    ||
			    var->blue.length    || var->transp.length   ||
			    var->red.msb_right  || var->green.msb_right ||
			    var->blue.msb_right || var->transp.msb_right)
				return -EINVAL;
		}

		if (!info->fbops->fb_check_var) {
			*var = info->var;
			goto done;
		}

		ret = info->fbops->fb_check_var(var, info);

		if (ret)
			goto done;

		if ((var->activate & FB_ACTIVATE_MASK) == FB_ACTIVATE_NOW) {
			struct fb_var_screeninfo old_var;
			struct fb_videomode mode;

			if (info->fbops->fb_get_caps) {
				ret = fb_check_caps(info, var, activate);

				if (ret)
					goto done;
			}

			old_var = info->var;
			info->var = *var;

			if (info->fbops->fb_set_par) {
				ret = info->fbops->fb_set_par(info);

				if (ret) {
					info->var = old_var;
					printk(KERN_WARNING "detected "
						"fb_set_par error, "
						"error code: %d\n", ret);
					goto done;
				}
			}

			fb_pan_display(info, &info->var);
			fb_set_cmap(&info->cmap, info);
			fb_var_to_videomode(&mode, &info->var);

			if (info->modelist.prev && info->modelist.next &&
			    !list_empty(&info->modelist))
				ret = fb_add_videomode(&mode, &info->modelist);

			if (!ret && (flags & FBINFO_MISC_USEREVENT)) {
				struct fb_event event;
				int evnt = (activate & FB_ACTIVATE_ALL) ?
					FB_EVENT_MODE_CHANGE_ALL :
					FB_EVENT_MODE_CHANGE;

				info->flags &= ~FBINFO_MISC_USEREVENT;
				event.info = info;
				event.data = &mode;
				fb_notifier_call_chain(evnt, &event);
			}
		}
	}

 done:
	return ret;
}
