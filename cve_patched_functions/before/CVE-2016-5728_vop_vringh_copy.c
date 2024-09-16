static int vop_vringh_copy(struct vop_vdev *vdev, struct vringh_kiov *iov,
			   void __user *ubuf, size_t len, bool read, int vr_idx,
			   size_t *out_len)
{
	int ret = 0;
	size_t partlen, tot_len = 0;

	while (len && iov->i < iov->used) {
		struct kvec *kiov = &iov->iov[iov->i];

		partlen = min(kiov->iov_len, len);
		if (read)
			ret = vop_virtio_copy_to_user(vdev, ubuf, partlen,
						      (u64)kiov->iov_base,
						      kiov->iov_len,
						      vr_idx);
		else
			ret = vop_virtio_copy_from_user(vdev, ubuf, partlen,
							(u64)kiov->iov_base,
							kiov->iov_len,
							vr_idx);
		if (ret) {
			dev_err(vop_dev(vdev), "%s %d err %d\n",
				__func__, __LINE__, ret);
			break;
		}
		len -= partlen;
		ubuf += partlen;
		tot_len += partlen;
		iov->consumed += partlen;
		kiov->iov_len -= partlen;
		kiov->iov_base += partlen;
		if (!kiov->iov_len) {
			/* Fix up old iov element then increment. */
			kiov->iov_len = iov->consumed;
			kiov->iov_base -= iov->consumed;

			iov->consumed = 0;
			iov->i++;
		}
	}
	*out_len = tot_len;
	return ret;
}
