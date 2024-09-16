static inline pgprot_t __get_dma_pgprot(struct dma_attrs *attrs, pgprot_t prot)
{
	prot = dma_get_attr(DMA_ATTR_WRITE_COMBINE, attrs) ?
			    pgprot_writecombine(prot) :
			    pgprot_dmacoherent(prot);
	return prot;
}
