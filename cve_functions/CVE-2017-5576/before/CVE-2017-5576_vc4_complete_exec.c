vc4_complete_exec(struct drm_device *dev, struct vc4_exec_info *exec)
{
	struct vc4_dev *vc4 = to_vc4_dev(dev);
	unsigned i;

	if (exec->bo) {
		for (i = 0; i < exec->bo_count; i++)
			drm_gem_object_unreference_unlocked(&exec->bo[i]->base);
		drm_free_large(exec->bo);
	}

	while (!list_empty(&exec->unref_list)) {
		struct vc4_bo *bo = list_first_entry(&exec->unref_list,
						     struct vc4_bo, unref_head);
		list_del(&bo->unref_head);
		drm_gem_object_unreference_unlocked(&bo->base.base);
	}

	mutex_lock(&vc4->power_lock);
	if (--vc4->power_refcount == 0) {
		pm_runtime_mark_last_busy(&vc4->v3d->pdev->dev);
		pm_runtime_put_autosuspend(&vc4->v3d->pdev->dev);
	}
	mutex_unlock(&vc4->power_lock);

	kfree(exec);
}
