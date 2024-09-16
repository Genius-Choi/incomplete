int platform_get_irq_byname(struct platform_device *dev, const char *name)
{
	struct resource *r;

	if (IS_ENABLED(CONFIG_OF_IRQ) && dev->dev.of_node) {
		int ret;

		ret = of_irq_get_byname(dev->dev.of_node, name);
		if (ret > 0 || ret == -EPROBE_DEFER)
			return ret;
	}

	r = platform_get_resource_byname(dev, IORESOURCE_IRQ, name);
	return r ? r->start : -ENXIO;
}
