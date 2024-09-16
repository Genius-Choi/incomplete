static void pte_list_remove(u64 *spte, unsigned long *pte_list)
{
	struct pte_list_desc *desc;
	struct pte_list_desc *prev_desc;
	int i;

	if (!*pte_list) {
		printk(KERN_ERR "pte_list_remove: %p 0->BUG\n", spte);
		BUG();
	} else if (!(*pte_list & 1)) {
		rmap_printk("pte_list_remove:  %p 1->0\n", spte);
		if ((u64 *)*pte_list != spte) {
			printk(KERN_ERR "pte_list_remove:  %p 1->BUG\n", spte);
			BUG();
		}
		*pte_list = 0;
	} else {
		rmap_printk("pte_list_remove:  %p many->many\n", spte);
		desc = (struct pte_list_desc *)(*pte_list & ~1ul);
		prev_desc = NULL;
		while (desc) {
			for (i = 0; i < PTE_LIST_EXT && desc->sptes[i]; ++i)
				if (desc->sptes[i] == spte) {
					pte_list_desc_remove_entry(pte_list,
							       desc, i,
							       prev_desc);
					return;
				}
			prev_desc = desc;
			desc = desc->more;
		}
		pr_err("pte_list_remove: %p many->many\n", spte);
		BUG();
	}
}
