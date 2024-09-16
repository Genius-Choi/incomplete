int kvm_io_bus_read(struct kvm *kvm, enum kvm_bus bus_idx, gpa_t addr,
		    int len, void *val)
{
	int idx;
	struct kvm_io_bus *bus;
	struct kvm_io_range range;

	range = (struct kvm_io_range) {
		.addr = addr,
		.len = len,
	};

	bus = srcu_dereference(kvm->buses[bus_idx], &kvm->srcu);
	idx = kvm_io_bus_get_first_dev(bus, addr, len);
	if (idx < 0)
		return -EOPNOTSUPP;

	while (idx < bus->dev_count &&
		kvm_io_bus_sort_cmp(&range, &bus->range[idx]) == 0) {
		if (!kvm_iodevice_read(bus->range[idx].dev, addr, len, val))
			return 0;
		idx++;
	}

	return -EOPNOTSUPP;
}
