static void hns_rcb_ring_pair_get_cfg(struct ring_pair_cb *ring_pair_cb)
{
	ring_pair_cb->q.handle = NULL;

	hns_rcb_ring_get_cfg(&ring_pair_cb->q, RX_RING);
	hns_rcb_ring_get_cfg(&ring_pair_cb->q, TX_RING);
}
