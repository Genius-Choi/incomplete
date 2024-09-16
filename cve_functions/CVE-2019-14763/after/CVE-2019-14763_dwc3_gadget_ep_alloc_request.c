static struct usb_request *dwc3_gadget_ep_alloc_request(struct usb_ep *ep,
	gfp_t gfp_flags)
{
	struct dwc3_request		*req;
	struct dwc3_ep			*dep = to_dwc3_ep(ep);

	req = kzalloc(sizeof(*req), gfp_flags);
	if (!req)
		return NULL;

	req->epnum	= dep->number;
	req->dep	= dep;

	dep->allocated_requests++;

	trace_dwc3_alloc_request(req);

	return &req->request;
}
