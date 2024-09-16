static u64 huge_pte_to_pagemap_entry(pte_t pte, int offset)
{
	u64 pme = 0;
	if (pte_present(pte))
		pme = PM_PFRAME(pte_pfn(pte) + offset)
			| PM_PSHIFT(PAGE_SHIFT) | PM_PRESENT;
	return pme;
}
