static int hns_rcb_get_port_in_comm(
	struct rcb_common_cb *rcb_common, int ring_idx)
{
	return ring_idx / (rcb_common->max_q_per_vf * rcb_common->max_vfn);
}
