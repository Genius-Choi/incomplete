i915_gem_execbuffer_relocate_slow(struct drm_device *dev,
				  struct drm_file *file,
				  struct intel_ring_buffer *ring,
				  struct list_head *objects,
				  struct eb_objects *eb,
				  struct drm_i915_gem_exec_object2 *exec,
				  int count)
{
	struct drm_i915_gem_relocation_entry *reloc;
	struct drm_i915_gem_object *obj;
	int *reloc_offset;
	int i, total, ret;

	/* We may process another execbuffer during the unlock... */
	while (!list_empty(objects)) {
		obj = list_first_entry(objects,
				       struct drm_i915_gem_object,
				       exec_list);
		list_del_init(&obj->exec_list);
		drm_gem_object_unreference(&obj->base);
	}

	mutex_unlock(&dev->struct_mutex);

	total = 0;
	for (i = 0; i < count; i++)
		total += exec[i].relocation_count;

	reloc_offset = drm_malloc_ab(count, sizeof(*reloc_offset));
	reloc = drm_malloc_ab(total, sizeof(*reloc));
	if (reloc == NULL || reloc_offset == NULL) {
		drm_free_large(reloc);
		drm_free_large(reloc_offset);
		mutex_lock(&dev->struct_mutex);
		return -ENOMEM;
	}

	total = 0;
	for (i = 0; i < count; i++) {
		struct drm_i915_gem_relocation_entry __user *user_relocs;

		user_relocs = (void __user *)(uintptr_t)exec[i].relocs_ptr;

		if (copy_from_user(reloc+total, user_relocs,
				   exec[i].relocation_count * sizeof(*reloc))) {
			ret = -EFAULT;
			mutex_lock(&dev->struct_mutex);
			goto err;
		}

		reloc_offset[i] = total;
		total += exec[i].relocation_count;
	}

	ret = i915_mutex_lock_interruptible(dev);
	if (ret) {
		mutex_lock(&dev->struct_mutex);
		goto err;
	}

	/* reacquire the objects */
	eb_reset(eb);
	for (i = 0; i < count; i++) {
		obj = to_intel_bo(drm_gem_object_lookup(dev, file,
							exec[i].handle));
		if (&obj->base == NULL) {
			DRM_DEBUG("Invalid object handle %d at index %d\n",
				   exec[i].handle, i);
			ret = -ENOENT;
			goto err;
		}

		list_add_tail(&obj->exec_list, objects);
		obj->exec_handle = exec[i].handle;
		obj->exec_entry = &exec[i];
		eb_add_object(eb, obj);
	}

	ret = i915_gem_execbuffer_reserve(ring, file, objects);
	if (ret)
		goto err;

	list_for_each_entry(obj, objects, exec_list) {
		int offset = obj->exec_entry - exec;
		ret = i915_gem_execbuffer_relocate_object_slow(obj, eb,
							       reloc + reloc_offset[offset]);
		if (ret)
			goto err;
	}

	/* Leave the user relocations as are, this is the painfully slow path,
	 * and we want to avoid the complication of dropping the lock whilst
	 * having buffers reserved in the aperture and so causing spurious
	 * ENOSPC for random operations.
	 */

err:
	drm_free_large(reloc);
	drm_free_large(reloc_offset);
	return ret;
}
