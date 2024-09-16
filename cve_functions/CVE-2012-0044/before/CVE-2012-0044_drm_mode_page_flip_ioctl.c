int drm_mode_page_flip_ioctl(struct drm_device *dev,
			     void *data, struct drm_file *file_priv)
{
	struct drm_mode_crtc_page_flip *page_flip = data;
	struct drm_mode_object *obj;
	struct drm_crtc *crtc;
	struct drm_framebuffer *fb;
	struct drm_pending_vblank_event *e = NULL;
	unsigned long flags;
	int ret = -EINVAL;

	if (page_flip->flags & ~DRM_MODE_PAGE_FLIP_FLAGS ||
	    page_flip->reserved != 0)
		return -EINVAL;

	mutex_lock(&dev->mode_config.mutex);
	obj = drm_mode_object_find(dev, page_flip->crtc_id, DRM_MODE_OBJECT_CRTC);
	if (!obj)
		goto out;
	crtc = obj_to_crtc(obj);

	if (crtc->fb == NULL) {
		/* The framebuffer is currently unbound, presumably
		 * due to a hotplug event, that userspace has not
		 * yet discovered.
		 */
		ret = -EBUSY;
		goto out;
	}

	if (crtc->funcs->page_flip == NULL)
		goto out;

	obj = drm_mode_object_find(dev, page_flip->fb_id, DRM_MODE_OBJECT_FB);
	if (!obj)
		goto out;
	fb = obj_to_fb(obj);

	if (page_flip->flags & DRM_MODE_PAGE_FLIP_EVENT) {
		ret = -ENOMEM;
		spin_lock_irqsave(&dev->event_lock, flags);
		if (file_priv->event_space < sizeof e->event) {
			spin_unlock_irqrestore(&dev->event_lock, flags);
			goto out;
		}
		file_priv->event_space -= sizeof e->event;
		spin_unlock_irqrestore(&dev->event_lock, flags);

		e = kzalloc(sizeof *e, GFP_KERNEL);
		if (e == NULL) {
			spin_lock_irqsave(&dev->event_lock, flags);
			file_priv->event_space += sizeof e->event;
			spin_unlock_irqrestore(&dev->event_lock, flags);
			goto out;
		}

		e->event.base.type = DRM_EVENT_FLIP_COMPLETE;
		e->event.base.length = sizeof e->event;
		e->event.user_data = page_flip->user_data;
		e->base.event = &e->event.base;
		e->base.file_priv = file_priv;
		e->base.destroy =
			(void (*) (struct drm_pending_event *)) kfree;
	}

	ret = crtc->funcs->page_flip(crtc, fb, e);
	if (ret) {
		spin_lock_irqsave(&dev->event_lock, flags);
		file_priv->event_space += sizeof e->event;
		spin_unlock_irqrestore(&dev->event_lock, flags);
		kfree(e);
	}

out:
	mutex_unlock(&dev->mode_config.mutex);
	return ret;
}
