static void unlock_expected_tids(struct qib_ctxtdata *rcd)
{
	struct qib_devdata *dd = rcd->dd;
	int ctxt_tidbase = rcd->ctxt * dd->rcvtidcnt;
	int i, cnt = 0, maxtid = ctxt_tidbase + dd->rcvtidcnt;

	for (i = ctxt_tidbase; i < maxtid; i++) {
		struct page *p = dd->pageshadow[i];
		dma_addr_t phys;

		if (!p)
			continue;

		phys = dd->physshadow[i];
		dd->physshadow[i] = dd->tidinvalid;
		dd->pageshadow[i] = NULL;
		pci_unmap_page(dd->pcidev, phys, PAGE_SIZE,
			       PCI_DMA_FROMDEVICE);
		qib_release_user_pages(&p, 1);
		cnt++;
	}
}
