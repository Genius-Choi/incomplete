static pte_t *lookup_pte(struct mm_struct *mm, unsigned long address)
{
	pgd_t *dir;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;
	pte_t entry;

	dir = pgd_offset(mm, address);
	if (pgd_none(*dir))
		return NULL;

	pud = pud_offset(dir, address);
	if (pud_none(*pud))
		return NULL;

	pmd = pmd_offset(pud, address);
	if (pmd_none(*pmd))
		return NULL;

	pte = pte_offset_kernel(pmd, address);
	entry = *pte;
	if (pte_none(entry) || !pte_present(entry))
		return NULL;

	return pte;
}
