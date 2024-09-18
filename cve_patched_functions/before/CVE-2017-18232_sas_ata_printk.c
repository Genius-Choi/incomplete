static int sas_ata_printk(const char *level, const struct domain_device *ddev,
			  const char *fmt, ...)
{
	struct ata_port *ap = ddev->sata_dev.ap;
	struct device *dev = &ddev->rphy->dev;
	struct va_format vaf;
	va_list args;
	int r;

	va_start(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	r = printk("%ssas: ata%u: %s: %pV",
		   level, ap->print_id, dev_name(dev), &vaf);

	va_end(args);

	return r;
}
