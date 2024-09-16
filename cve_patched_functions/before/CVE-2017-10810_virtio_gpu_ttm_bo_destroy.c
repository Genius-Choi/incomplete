static void virtio_gpu_ttm_bo_destroy(struct ttm_buffer_object *tbo)
{
	struct virtio_gpu_object *bo;
	struct virtio_gpu_device *vgdev;

	bo = container_of(tbo, struct virtio_gpu_object, tbo);
	vgdev = (struct virtio_gpu_device *)bo->gem_base.dev->dev_private;

	if (bo->hw_res_handle)
		virtio_gpu_cmd_unref_resource(vgdev, bo->hw_res_handle);
	if (bo->pages)
		virtio_gpu_object_free_sg_table(bo);
	drm_gem_object_release(&bo->gem_base);
	kfree(bo);
}
