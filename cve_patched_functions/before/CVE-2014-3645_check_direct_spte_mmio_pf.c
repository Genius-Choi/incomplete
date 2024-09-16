static bool check_direct_spte_mmio_pf(u64 spte)
{
	return __check_direct_spte_mmio_pf(spte);
}
