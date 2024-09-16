static void sort_memslots(struct kvm_memslots *slots)
{
	int i;

	sort(slots->memslots, KVM_MEM_SLOTS_NUM,
	      sizeof(struct kvm_memory_slot), cmp_memslot, NULL);

	for (i = 0; i < KVM_MEM_SLOTS_NUM; i++)
		slots->id_to_index[slots->memslots[i].id] = i;
}
