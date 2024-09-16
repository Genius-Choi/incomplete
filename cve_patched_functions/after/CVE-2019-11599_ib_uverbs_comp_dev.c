static void ib_uverbs_comp_dev(struct ib_uverbs_device *dev)
{
	complete(&dev->comp);
}
