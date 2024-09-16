GetFirewallStatus(struct upnphttp * h, const char * action, const char * ns)
{
	static const char resp[] =
		"<u:%sResponse "
		"xmlns:u=\"%s\">"
		"<FirewallEnabled>%d</FirewallEnabled>"
		"<InboundPinholeAllowed>%d</InboundPinholeAllowed>"
		"</u:%sResponse>";

	char body[512];
	int bodylen;

	bodylen = snprintf(body, sizeof(body), resp,
		action, ns, /*"urn:schemas-upnp-org:service:WANIPv6FirewallControl:1",*/
	    GETFLAG(IPV6FCFWDISABLEDMASK) ? 0 : 1,
	    GETFLAG(IPV6FCINBOUNDDISALLOWEDMASK) ? 0 : 1,
	    action);
	BuildSendAndCloseSoapResp(h, body, bodylen);
}
