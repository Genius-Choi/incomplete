void hns_rcb_init_hw(struct ring_pair_cb *ring)
{
	hns_rcb_ring_init(ring, RX_RING);
	hns_rcb_ring_init(ring, TX_RING);
}
