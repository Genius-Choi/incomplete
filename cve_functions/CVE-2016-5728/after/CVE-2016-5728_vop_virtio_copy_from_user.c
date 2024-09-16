static int vop_virtio_copy_from_user(struct vop_vdev *vdev, void __user *ubuf,
				     size_t len, u64 daddr, size_t dlen,
				     int vr_idx)
{
	struct vop_device *vpdev = vdev->vpdev;
	void __iomem *dbuf = vpdev->hw_ops->ioremap(vpdev, daddr, len);
	struct vop_vringh *vvr = &vdev->vvr[vr_idx];
	struct vop_info *vi = dev_get_drvdata(&vdev->vpdev->dev);
	size_t dma_alignment = 1 << vi->dma_ch->device->copy_align;
	bool x200 = is_dma_copy_aligned(vi->dma_ch->device, 1, 1, 1);
	size_t partlen;
	bool dma = VOP_USE_DMA;
	int err = 0;

	if (daddr & (dma_alignment - 1)) {
		vdev->tx_dst_unaligned += len;
		dma = false;
	} else if (ALIGN(len, dma_alignment) > dlen) {
		vdev->tx_len_unaligned += len;
		dma = false;
	}

	if (!dma)
		goto memcpy;

	/*
	 * X100 uses DMA addresses as seen by the card so adding
	 * the aperture base is not required for DMA. However x200
	 * requires DMA addresses to be an offset into the bar so
	 * add the aperture base for x200.
	 */
	if (x200)
		daddr += vpdev->aper->pa;
	while (len) {
		partlen = min_t(size_t, len, VOP_INT_DMA_BUF_SIZE);

		if (copy_from_user(vvr->buf, ubuf, partlen)) {
			err = -EFAULT;
			dev_err(vop_dev(vdev), "%s %d err %d\n",
				__func__, __LINE__, err);
			goto err;
		}
		err = vop_sync_dma(vdev, daddr, vvr->buf_da,
				   ALIGN(partlen, dma_alignment));
		if (err) {
			dev_err(vop_dev(vdev), "%s %d err %d\n",
				__func__, __LINE__, err);
			goto err;
		}
		daddr += partlen;
		ubuf += partlen;
		dbuf += partlen;
		vdev->out_bytes_dma += partlen;
		vdev->out_bytes += partlen;
		len -= partlen;
	}
memcpy:
	/*
	 * We are copying to IO below and should ideally use something
	 * like copy_from_user_toio(..) if it existed.
	 */
	if (copy_from_user((void __force *)dbuf, ubuf, len)) {
		err = -EFAULT;
		dev_err(vop_dev(vdev), "%s %d err %d\n",
			__func__, __LINE__, err);
		goto err;
	}
	vdev->out_bytes += len;
	err = 0;
err:
	vpdev->hw_ops->iounmap(vpdev, dbuf);
	dev_dbg(vop_dev(vdev),
		"%s: ubuf %p dbuf %p len 0x%lx vr_idx 0x%x\n",
		__func__, ubuf, dbuf, len, vr_idx);
	return err;
}
