int kvm_io_bus_sort_cmp(const void *p1, const void *p2)
{
	const struct kvm_io_range *r1 = p1;
	const struct kvm_io_range *r2 = p2;

	if (r1->addr < r2->addr)
		return -1;
	if (r1->addr + r1->len > r2->addr + r2->len)
		return 1;
	return 0;
}
