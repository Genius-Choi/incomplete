void __split_huge_page_pmd(struct mm_struct *mm, pmd_t *pmd)
{
	struct page *page;

	spin_lock(&mm->page_table_lock);
	if (unlikely(!pmd_trans_huge(*pmd))) {
		spin_unlock(&mm->page_table_lock);
		return;
	}
	page = pmd_page(*pmd);
	VM_BUG_ON(!page_count(page));
	get_page(page);
	spin_unlock(&mm->page_table_lock);

	split_huge_page(page);

	put_page(page);
	BUG_ON(pmd_trans_huge(*pmd));
}
