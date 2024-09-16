static int cmp_memslot(const void *slot1, const void *slot2)
{
	struct kvm_memory_slot *s1, *s2;

	s1 = (struct kvm_memory_slot *)slot1;
	s2 = (struct kvm_memory_slot *)slot2;

	if (s1->npages < s2->npages)
		return 1;
	if (s1->npages > s2->npages)
		return -1;

	return 0;
}
