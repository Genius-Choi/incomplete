vc4_wait_bo_ioctl(struct drm_device *dev, void *data,
		  struct drm_file *file_priv)
{
	int ret;
	struct drm_vc4_wait_bo *args = data;
	struct drm_gem_object *gem_obj;
	struct vc4_bo *bo;

	if (args->pad != 0)
		return -EINVAL;

	gem_obj = drm_gem_object_lookup(file_priv, args->handle);
	if (!gem_obj) {
		DRM_ERROR("Failed to look up GEM BO %d\n", args->handle);
		return -EINVAL;
	}
	bo = to_vc4_bo(gem_obj);

	ret = vc4_wait_for_seqno_ioctl_helper(dev, bo->seqno,
					      &args->timeout_ns);

	drm_gem_object_unreference_unlocked(gem_obj);
	return ret;
}
