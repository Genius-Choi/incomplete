int platform_irq_count(struct platform_device *dev)
{
	int ret, nr = 0;

	while ((ret = platform_get_irq(dev, nr)) >= 0)
		nr++;

	if (ret == -EPROBE_DEFER)
		return ret;

	return nr;
}
