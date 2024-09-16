vhost_scsi_ioctl(struct file *f,
		 unsigned int ioctl,
		 unsigned long arg)
{
	struct vhost_scsi *vs = f->private_data;
	struct vhost_scsi_target backend;
	void __user *argp = (void __user *)arg;
	u64 __user *featurep = argp;
	u32 __user *eventsp = argp;
	u32 events_missed;
	u64 features;
	int r, abi_version = VHOST_SCSI_ABI_VERSION;
	struct vhost_virtqueue *vq = &vs->vqs[VHOST_SCSI_VQ_EVT].vq;

	switch (ioctl) {
	case VHOST_SCSI_SET_ENDPOINT:
		if (copy_from_user(&backend, argp, sizeof backend))
			return -EFAULT;
		if (backend.reserved != 0)
			return -EOPNOTSUPP;

		return vhost_scsi_set_endpoint(vs, &backend);
	case VHOST_SCSI_CLEAR_ENDPOINT:
		if (copy_from_user(&backend, argp, sizeof backend))
			return -EFAULT;
		if (backend.reserved != 0)
			return -EOPNOTSUPP;

		return vhost_scsi_clear_endpoint(vs, &backend);
	case VHOST_SCSI_GET_ABI_VERSION:
		if (copy_to_user(argp, &abi_version, sizeof abi_version))
			return -EFAULT;
		return 0;
	case VHOST_SCSI_SET_EVENTS_MISSED:
		if (get_user(events_missed, eventsp))
			return -EFAULT;
		mutex_lock(&vq->mutex);
		vs->vs_events_missed = events_missed;
		mutex_unlock(&vq->mutex);
		return 0;
	case VHOST_SCSI_GET_EVENTS_MISSED:
		mutex_lock(&vq->mutex);
		events_missed = vs->vs_events_missed;
		mutex_unlock(&vq->mutex);
		if (put_user(events_missed, eventsp))
			return -EFAULT;
		return 0;
	case VHOST_GET_FEATURES:
		features = VHOST_SCSI_FEATURES;
		if (copy_to_user(featurep, &features, sizeof features))
			return -EFAULT;
		return 0;
	case VHOST_SET_FEATURES:
		if (copy_from_user(&features, featurep, sizeof features))
			return -EFAULT;
		return vhost_scsi_set_features(vs, features);
	default:
		mutex_lock(&vs->dev.mutex);
		r = vhost_dev_ioctl(&vs->dev, ioctl, argp);
		/* TODO: flush backend after dev ioctl. */
		if (r == -ENOIOCTLCMD)
			r = vhost_vring_ioctl(&vs->dev, ioctl, argp);
		mutex_unlock(&vs->dev.mutex);
		return r;
	}
}
