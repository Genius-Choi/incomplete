static int vop_virtio_add_device(struct vop_vdev *vdev,
				 struct mic_device_desc *argp)
{
	struct vop_info *vi = vdev->vi;
	struct vop_device *vpdev = vi->vpdev;
	struct mic_device_desc *dd = NULL;
	struct mic_vqconfig *vqconfig;
	int vr_size, i, j, ret;
	u8 type = 0;
	s8 db = -1;
	char irqname[16];
	struct mic_bootparam *bootparam;
	u16 num;
	dma_addr_t vr_addr;

	bootparam = vpdev->hw_ops->get_dp(vpdev);
	init_waitqueue_head(&vdev->waitq);
	INIT_LIST_HEAD(&vdev->list);
	vdev->vpdev = vpdev;

	ret = vop_copy_dp_entry(vdev, argp, &type, &dd);
	if (ret) {
		dev_err(vop_dev(vdev), "%s %d err %d\n",
			__func__, __LINE__, ret);
		kfree(vdev);
		return ret;
	}

	vop_init_device_ctrl(vdev, dd);

	vdev->dd = dd;
	vdev->virtio_id = type;
	vqconfig = mic_vq_config(dd);
	INIT_WORK(&vdev->virtio_bh_work, vop_bh_handler);

	for (i = 0; i < dd->num_vq; i++) {
		struct vop_vringh *vvr = &vdev->vvr[i];
		struct mic_vring *vr = &vdev->vvr[i].vring;

		num = le16_to_cpu(vqconfig[i].num);
		mutex_init(&vvr->vr_mutex);
		vr_size = PAGE_ALIGN(vring_size(num, MIC_VIRTIO_RING_ALIGN) +
			sizeof(struct _mic_vring_info));
		vr->va = (void *)
			__get_free_pages(GFP_KERNEL | __GFP_ZERO,
					 get_order(vr_size));
		if (!vr->va) {
			ret = -ENOMEM;
			dev_err(vop_dev(vdev), "%s %d err %d\n",
				__func__, __LINE__, ret);
			goto err;
		}
		vr->len = vr_size;
		vr->info = vr->va + vring_size(num, MIC_VIRTIO_RING_ALIGN);
		vr->info->magic = cpu_to_le32(MIC_MAGIC + vdev->virtio_id + i);
		vr_addr = dma_map_single(&vpdev->dev, vr->va, vr_size,
					 DMA_BIDIRECTIONAL);
		if (dma_mapping_error(&vpdev->dev, vr_addr)) {
			free_pages((unsigned long)vr->va, get_order(vr_size));
			ret = -ENOMEM;
			dev_err(vop_dev(vdev), "%s %d err %d\n",
				__func__, __LINE__, ret);
			goto err;
		}
		vqconfig[i].address = cpu_to_le64(vr_addr);

		vring_init(&vr->vr, num, vr->va, MIC_VIRTIO_RING_ALIGN);
		ret = vringh_init_kern(&vvr->vrh,
				       *(u32 *)mic_vq_features(vdev->dd),
				       num, false, vr->vr.desc, vr->vr.avail,
				       vr->vr.used);
		if (ret) {
			dev_err(vop_dev(vdev), "%s %d err %d\n",
				__func__, __LINE__, ret);
			goto err;
		}
		vringh_kiov_init(&vvr->riov, NULL, 0);
		vringh_kiov_init(&vvr->wiov, NULL, 0);
		vvr->head = USHRT_MAX;
		vvr->vdev = vdev;
		vvr->vrh.notify = _vop_notify;
		dev_dbg(&vpdev->dev,
			"%s %d index %d va %p info %p vr_size 0x%x\n",
			__func__, __LINE__, i, vr->va, vr->info, vr_size);
		vvr->buf = (void *)__get_free_pages(GFP_KERNEL,
					get_order(VOP_INT_DMA_BUF_SIZE));
		vvr->buf_da = dma_map_single(&vpdev->dev,
					  vvr->buf, VOP_INT_DMA_BUF_SIZE,
					  DMA_BIDIRECTIONAL);
	}

	snprintf(irqname, sizeof(irqname), "vop%dvirtio%d", vpdev->index,
		 vdev->virtio_id);
	vdev->virtio_db = vpdev->hw_ops->next_db(vpdev);
	vdev->virtio_cookie = vpdev->hw_ops->request_irq(vpdev,
			_vop_virtio_intr_handler, irqname, vdev,
			vdev->virtio_db);
	if (IS_ERR(vdev->virtio_cookie)) {
		ret = PTR_ERR(vdev->virtio_cookie);
		dev_dbg(&vpdev->dev, "request irq failed\n");
		goto err;
	}

	vdev->dc->c2h_vdev_db = vdev->virtio_db;

	/*
	 * Order the type update with previous stores. This write barrier
	 * is paired with the corresponding read barrier before the uncached
	 * system memory read of the type, on the card while scanning the
	 * device page.
	 */
	smp_wmb();
	dd->type = type;
	argp->type = type;

	if (bootparam) {
		db = bootparam->h2c_config_db;
		if (db != -1)
			vpdev->hw_ops->send_intr(vpdev, db);
	}
	dev_dbg(&vpdev->dev, "Added virtio id %d db %d\n", dd->type, db);
	return 0;
err:
	vqconfig = mic_vq_config(dd);
	for (j = 0; j < i; j++) {
		struct vop_vringh *vvr = &vdev->vvr[j];

		dma_unmap_single(&vpdev->dev, le64_to_cpu(vqconfig[j].address),
				 vvr->vring.len, DMA_BIDIRECTIONAL);
		free_pages((unsigned long)vvr->vring.va,
			   get_order(vvr->vring.len));
	}
	return ret;
}
