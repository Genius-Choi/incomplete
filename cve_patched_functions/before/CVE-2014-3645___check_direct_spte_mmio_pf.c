static bool __check_direct_spte_mmio_pf(u64 spte)
{
	union split_spte sspte = (union split_spte)spte;
	u32 high_mmio_mask = shadow_mmio_mask >> 32;

	/* It is valid if the spte is zapped. */
	if (spte == 0ull)
		return true;

	/* It is valid if the spte is being zapped. */
	if (sspte.spte_low == 0ull &&
	    (sspte.spte_high & high_mmio_mask) == high_mmio_mask)
		return true;

	return false;
}
