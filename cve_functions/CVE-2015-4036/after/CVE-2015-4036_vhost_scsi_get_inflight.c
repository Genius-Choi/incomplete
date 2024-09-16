vhost_scsi_get_inflight(struct vhost_virtqueue *vq)
{
	struct vhost_scsi_inflight *inflight;
	struct vhost_scsi_virtqueue *svq;

	svq = container_of(vq, struct vhost_scsi_virtqueue, vq);
	inflight = &svq->inflights[svq->inflight_idx];
	kref_get(&inflight->kref);

	return inflight;
}
