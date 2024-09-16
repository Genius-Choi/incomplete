static int virtnet_busy_poll(struct napi_struct *napi)
{
	struct receive_queue *rq =
		container_of(napi, struct receive_queue, napi);
	struct virtnet_info *vi = rq->vq->vdev->priv;
	int r, received = 0, budget = 4;

	if (!(vi->status & VIRTIO_NET_S_LINK_UP))
		return LL_FLUSH_FAILED;

	if (!napi_schedule_prep(napi))
		return LL_FLUSH_BUSY;

	virtqueue_disable_cb(rq->vq);

again:
	received += virtnet_receive(rq, budget);

	r = virtqueue_enable_cb_prepare(rq->vq);
	clear_bit(NAPI_STATE_SCHED, &napi->state);
	if (unlikely(virtqueue_poll(rq->vq, r)) &&
	    napi_schedule_prep(napi)) {
		virtqueue_disable_cb(rq->vq);
		if (received < budget) {
			budget -= received;
			goto again;
		} else {
			__napi_schedule(napi);
		}
	}

	return received;
}
