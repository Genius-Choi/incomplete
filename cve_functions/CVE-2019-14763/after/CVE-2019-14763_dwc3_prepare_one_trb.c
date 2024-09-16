static void dwc3_prepare_one_trb(struct dwc3_ep *dep,
		struct dwc3_request *req, unsigned chain, unsigned node)
{
	struct dwc3_trb		*trb;
	unsigned		length = req->request.length;
	unsigned		stream_id = req->request.stream_id;
	unsigned		short_not_ok = req->request.short_not_ok;
	unsigned		no_interrupt = req->request.no_interrupt;
	dma_addr_t		dma = req->request.dma;

	trb = &dep->trb_pool[dep->trb_enqueue];

	if (!req->trb) {
		dwc3_gadget_move_started_request(req);
		req->trb = trb;
		req->trb_dma = dwc3_trb_dma_offset(dep, trb);
		dep->queued_requests++;
	}

	__dwc3_prepare_one_trb(dep, trb, dma, length, chain, node,
			stream_id, short_not_ok, no_interrupt);
}
