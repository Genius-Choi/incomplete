static void release_all_pte_pages(pte_t *pte)
{
	release_pte_pages(pte, pte + HPAGE_PMD_NR);
}
