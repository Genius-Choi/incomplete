int drm_mode_attachmode_crtc(struct drm_device *dev, struct drm_crtc *crtc,
			     struct drm_display_mode *mode)
{
	struct drm_connector *connector;
	int ret = 0;
	struct drm_display_mode *dup_mode;
	int need_dup = 0;
	list_for_each_entry(connector, &dev->mode_config.connector_list, head) {
		if (!connector->encoder)
			break;
		if (connector->encoder->crtc == crtc) {
			if (need_dup)
				dup_mode = drm_mode_duplicate(dev, mode);
			else
				dup_mode = mode;
			ret = drm_mode_attachmode(dev, connector, dup_mode);
			if (ret)
				return ret;
			need_dup = 1;
		}
	}
	return 0;
}
