static void show_bus(struct udevice *bus)
{
	struct udevice *dev;

	printf("Bus %d:\t%s", dev_seq(bus), bus->name);
	if (device_active(bus))
		printf("  (active %d)", dev_seq(bus));
	printf("\n");
	for (device_find_first_child(bus, &dev);
	     dev;
	     device_find_next_child(&dev)) {
		struct dm_i2c_chip *chip = dev_get_parent_plat(dev);

		printf("   %02x: %s, offset len %x, flags %x\n",
		       chip->chip_addr, dev->name, chip->offset_len,
		       chip->flags);
	}
}
