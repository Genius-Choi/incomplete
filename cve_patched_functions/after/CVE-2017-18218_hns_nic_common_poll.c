static int hns_nic_common_poll(struct napi_struct *napi, int budget)
{
	int clean_complete = 0;
	struct hns_nic_ring_data *ring_data =
		container_of(napi, struct hns_nic_ring_data, napi);
	struct hnae_ring *ring = ring_data->ring;

try_again:
	clean_complete += ring_data->poll_one(
				ring_data, budget - clean_complete,
				ring_data->ex_process);

	if (clean_complete < budget) {
		if (ring_data->fini_process(ring_data)) {
			napi_complete(napi);
			ring->q->handle->dev->ops->toggle_ring_irq(ring, 0);
		} else {
			goto try_again;
		}
	}

	return clean_complete;
}
