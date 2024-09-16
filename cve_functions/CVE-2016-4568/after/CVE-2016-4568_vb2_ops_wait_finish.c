void vb2_ops_wait_finish(struct vb2_queue *vq)
{
	mutex_lock(vq->lock);
}
