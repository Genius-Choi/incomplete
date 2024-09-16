static u64 swap_pte_to_pagemap_entry(pte_t pte)
{
	swp_entry_t e = pte_to_swp_entry(pte);
	return swp_type(e) | (swp_offset(e) << MAX_SWAPFILES_SHIFT);
}
