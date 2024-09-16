static void __iomem *hns_ppe_get_iobase(struct ppe_common_cb *ppe_common,
					int ppe_idx)
{
	return ppe_common->dsaf_dev->ppe_base + ppe_idx * PPE_REG_OFFSET;
}
