static int is_rmap_spte(u64 pte)
{
	return is_shadow_present_pte(pte);
}
