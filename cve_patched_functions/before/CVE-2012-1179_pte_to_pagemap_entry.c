static u64 pte_to_pagemap_entry(pte_t pte)
{
	u64 pme = 0;
	if (is_swap_pte(pte))
		pme = PM_PFRAME(swap_pte_to_pagemap_entry(pte))
			| PM_PSHIFT(PAGE_SHIFT) | PM_SWAP;
	else if (pte_present(pte))
		pme = PM_PFRAME(pte_pfn(pte))
			| PM_PSHIFT(PAGE_SHIFT) | PM_PRESENT;
	return pme;
}
