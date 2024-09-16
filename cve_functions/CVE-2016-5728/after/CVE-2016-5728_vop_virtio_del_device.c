static void vop_virtio_del_device(struct vop_vdev *vdev)
{
	struct vop_info *vi = vdev->vi;
	struct vop_device *vpdev = vdev->vpdev;
	int i;
	struct mic_vqconfig *vqconfig;
	struct mic_bootparam *bootparam = vpdev->hw_ops->get_dp(vpdev);

	if (!bootparam)
		goto skip_hot_remove;
	vop_dev_remove(vi, vdev->dc, vpdev);
skip_hot_remove:
	vpdev->hw_ops->free_irq(vpdev, vdev->virtio_cookie, vdev);
	flush_work(&vdev->virtio_bh_work);
	vqconfig = mic_vq_config(vdev->dd);
	for (i = 0; i < vdev->dd->num_vq; i++) {
		struct vop_vringh *vvr = &vdev->vvr[i];

		dma_unmap_single(&vpdev->dev,
				 vvr->buf_da, VOP_INT_DMA_BUF_SIZE,
				 DMA_BIDIRECTIONAL);
		free_pages((unsigned long)vvr->buf,
			   get_order(VOP_INT_DMA_BUF_SIZE));
		vringh_kiov_cleanup(&vvr->riov);
		vringh_kiov_cleanup(&vvr->wiov);
		dma_unmap_single(&vpdev->dev, le64_to_cpu(vqconfig[i].address),
				 vvr->vring.len, DMA_BIDIRECTIONAL);
		free_pages((unsigned long)vvr->vring.va,
			   get_order(vvr->vring.len));
	}
	/*
	 * Order the type update with previous stores. This write barrier
	 * is paired with the corresponding read barrier before the uncached
	 * system memory read of the type, on the card while scanning the
	 * device page.
	 */
	smp_wmb();
	vdev->dd->type = -1;
}
