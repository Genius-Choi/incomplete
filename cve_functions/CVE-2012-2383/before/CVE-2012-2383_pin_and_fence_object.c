pin_and_fence_object(struct drm_i915_gem_object *obj,
		     struct intel_ring_buffer *ring)
{
	struct drm_i915_gem_exec_object2 *entry = obj->exec_entry;
	bool has_fenced_gpu_access = INTEL_INFO(ring->dev)->gen < 4;
	bool need_fence, need_mappable;
	int ret;

	need_fence =
		has_fenced_gpu_access &&
		entry->flags & EXEC_OBJECT_NEEDS_FENCE &&
		obj->tiling_mode != I915_TILING_NONE;
	need_mappable =
		entry->relocation_count ? true : need_fence;

	ret = i915_gem_object_pin(obj, entry->alignment, need_mappable);
	if (ret)
		return ret;

	if (has_fenced_gpu_access) {
		if (entry->flags & EXEC_OBJECT_NEEDS_FENCE) {
			if (obj->tiling_mode) {
				ret = i915_gem_object_get_fence(obj, ring);
				if (ret)
					goto err_unpin;

				entry->flags |= __EXEC_OBJECT_HAS_FENCE;
				i915_gem_object_pin_fence(obj);
			} else {
				ret = i915_gem_object_put_fence(obj);
				if (ret)
					goto err_unpin;
			}
			obj->pending_fenced_gpu_access = true;
		}
	}

	entry->offset = obj->gtt_offset;
	return 0;

err_unpin:
	i915_gem_object_unpin(obj);
	return ret;
}
