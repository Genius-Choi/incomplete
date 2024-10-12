int svc_rdma_post_recv(struct svcxprt_rdma *xprt, gfp_t flags)
{
	struct ib_recv_wr recv_wr, *bad_recv_wr;
	struct svc_rdma_op_ctxt *ctxt;
	struct page *page;
	dma_addr_t pa;
	int sge_no;
	int buflen;
	int ret;

	ctxt = svc_rdma_get_context(xprt);
	buflen = 0;
	ctxt->direction = DMA_FROM_DEVICE;
	ctxt->cqe.done = svc_rdma_wc_receive;
	for (sge_no = 0; buflen < xprt->sc_max_req_size; sge_no++) {
		if (sge_no >= xprt->sc_max_sge) {
			pr_err("svcrdma: Too many sges (%d)\n", sge_no);
			goto err_put_ctxt;
		}
		page = alloc_page(flags);
		if (!page)
			goto err_put_ctxt;
		ctxt->pages[sge_no] = page;
		pa = ib_dma_map_page(xprt->sc_cm_id->device,
				     page, 0, PAGE_SIZE,
				     DMA_FROM_DEVICE);
		if (ib_dma_mapping_error(xprt->sc_cm_id->device, pa))
			goto err_put_ctxt;
		svc_rdma_count_mappings(xprt, ctxt);
		ctxt->sge[sge_no].addr = pa;
		ctxt->sge[sge_no].length = PAGE_SIZE;
		ctxt->sge[sge_no].lkey = xprt->sc_pd->local_dma_lkey;
		ctxt->count = sge_no + 1;
		buflen += PAGE_SIZE;
	}
	recv_wr.next = NULL;
	recv_wr.sg_list = &ctxt->sge[0];
	recv_wr.num_sge = ctxt->count;
	recv_wr.wr_cqe = &ctxt->cqe;

	svc_xprt_get(&xprt->sc_xprt);
	ret = ib_post_recv(xprt->sc_qp, &recv_wr, &bad_recv_wr);
	if (ret) {
		svc_rdma_unmap_dma(ctxt);
		svc_rdma_put_context(ctxt, 1);
		svc_xprt_put(&xprt->sc_xprt);
	}
	return ret;

 err_put_ctxt:
	svc_rdma_unmap_dma(ctxt);
	svc_rdma_put_context(ctxt, 1);
	return -ENOMEM;
}
