concat_gen_fifos(
	void *first,
	void *second
	)
{
	gen_fifo *pf1;
	gen_fifo *pf2;

	pf1 = first;
	pf2 = second;
	if (NULL == pf1)
		return pf2;
	else if (NULL == pf2)
		return pf1;

	CONCAT_FIFO(*pf1, *pf2, link);
	free(pf2);

	return pf1;
}
