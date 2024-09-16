append_gen_fifo(
	void *fifo,
	void *entry
	)
{
	gen_fifo *pf;
	gen_node *pe;

	pf = fifo;
	pe = entry;
	if (NULL == pf)
		pf = emalloc_zero(sizeof(*pf));
	if (pe != NULL)
		LINK_FIFO(*pf, pe, link);

	return pf;
}
