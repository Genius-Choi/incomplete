static int dwc3_gadget_start_config(struct dwc3 *dwc, struct dwc3_ep *dep)
{
	struct dwc3_gadget_ep_cmd_params params;
	u32			cmd;
	int			i;
	int			ret;

	if (dep->number)
		return 0;

	memset(&params, 0x00, sizeof(params));
	cmd = DWC3_DEPCMD_DEPSTARTCFG;

	ret = dwc3_send_gadget_ep_cmd(dep, cmd, &params);
	if (ret)
		return ret;

	for (i = 0; i < DWC3_ENDPOINTS_NUM; i++) {
		struct dwc3_ep *dep = dwc->eps[i];

		if (!dep)
			continue;

		ret = dwc3_gadget_set_xfer_resource(dwc, dep);
		if (ret)
			return ret;
	}

	return 0;
}
