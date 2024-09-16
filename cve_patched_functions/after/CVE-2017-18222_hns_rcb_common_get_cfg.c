int hns_rcb_common_get_cfg(struct dsaf_device *dsaf_dev,
			   int comm_index)
{
	struct rcb_common_cb *rcb_common;
	enum dsaf_mode dsaf_mode = dsaf_dev->dsaf_mode;
	u16 max_vfn;
	u16 max_q_per_vf;
	int ring_num = hns_rcb_get_ring_num(dsaf_dev);

	rcb_common =
		devm_kzalloc(dsaf_dev->dev, sizeof(*rcb_common) +
			ring_num * sizeof(struct ring_pair_cb), GFP_KERNEL);
	if (!rcb_common) {
		dev_err(dsaf_dev->dev, "rcb common devm_kzalloc fail!\n");
		return -ENOMEM;
	}
	rcb_common->comm_index = comm_index;
	rcb_common->ring_num = ring_num;
	rcb_common->dsaf_dev = dsaf_dev;

	rcb_common->desc_num = dsaf_dev->desc_num;

	hns_rcb_get_queue_mode(dsaf_mode, &max_vfn, &max_q_per_vf);
	rcb_common->max_vfn = max_vfn;
	rcb_common->max_q_per_vf = max_q_per_vf;

	rcb_common->io_base = hns_rcb_common_get_vaddr(rcb_common);
	rcb_common->phy_base = hns_rcb_common_get_paddr(rcb_common);

	dsaf_dev->rcb_common[comm_index] = rcb_common;
	return 0;
}
