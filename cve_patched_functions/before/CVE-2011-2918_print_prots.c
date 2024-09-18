static inline void print_prots(pgprot_t prot)
{
	printk("prot is 0x%016llx\n",pgprot_val(prot));

	printk("%s %s %s %s %s\n",PPROT(_PAGE_SHARED),PPROT(_PAGE_READ),
	       PPROT(_PAGE_EXECUTE),PPROT(_PAGE_WRITE),PPROT(_PAGE_USER));
}
