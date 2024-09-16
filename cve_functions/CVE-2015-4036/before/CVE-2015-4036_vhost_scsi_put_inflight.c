static void vhost_scsi_put_inflight(struct vhost_scsi_inflight *inflight)
{
	kref_put(&inflight->kref, vhost_scsi_done_inflight);
}
