static void set_emss(struct iwch_ep *ep, u16 opt)
{
	PDBG("%s ep %p opt %u\n", __func__, ep, opt);
	ep->emss = T3C_DATA(ep->com.tdev)->mtus[G_TCPOPT_MSS(opt)] - 40;
	if (G_TCPOPT_TSTAMP(opt))
		ep->emss -= 12;
	if (ep->emss < 128)
		ep->emss = 128;
	PDBG("emss=%d\n", ep->emss);
}
