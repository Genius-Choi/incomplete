static unsigned int get_user_insn(unsigned long tpc)
{
	pgd_t *pgdp = pgd_offset(current->mm, tpc);
	pud_t *pudp;
	pmd_t *pmdp;
	pte_t *ptep, pte;
	unsigned long pa;
	u32 insn = 0;
	unsigned long pstate;

	if (pgd_none(*pgdp))
		goto outret;
	pudp = pud_offset(pgdp, tpc);
	if (pud_none(*pudp))
		goto outret;
	pmdp = pmd_offset(pudp, tpc);
	if (pmd_none(*pmdp))
		goto outret;

	/* This disables preemption for us as well. */
	__asm__ __volatile__("rdpr %%pstate, %0" : "=r" (pstate));
	__asm__ __volatile__("wrpr %0, %1, %%pstate"
				: : "r" (pstate), "i" (PSTATE_IE));
	ptep = pte_offset_map(pmdp, tpc);
	pte = *ptep;
	if (!pte_present(pte))
		goto out;

	pa  = (pte_pfn(pte) << PAGE_SHIFT);
	pa += (tpc & ~PAGE_MASK);

	/* Use phys bypass so we don't pollute dtlb/dcache. */
	__asm__ __volatile__("lduwa [%1] %2, %0"
			     : "=r" (insn)
			     : "r" (pa), "i" (ASI_PHYS_USE_EC));

out:
	pte_unmap(ptep);
	__asm__ __volatile__("wrpr %0, 0x0, %%pstate" : : "r" (pstate));
outret:
	return insn;
}
