void drm_mode_probed_add(struct drm_connector *connector,
			 struct drm_display_mode *mode)
{
	list_add(&mode->head, &connector->probed_modes);
}
