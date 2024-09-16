int virtio_gpu_object_kmap(struct virtio_gpu_object *bo, void **ptr)
{
	bool is_iomem;
	int r;

	if (bo->vmap) {
		if (ptr)
			*ptr = bo->vmap;
		return 0;
	}
	r = ttm_bo_kmap(&bo->tbo, 0, bo->tbo.num_pages, &bo->kmap);
	if (r)
		return r;
	bo->vmap = ttm_kmap_obj_virtual(&bo->kmap, &is_iomem);
	if (ptr)
		*ptr = bo->vmap;
	return 0;
}
