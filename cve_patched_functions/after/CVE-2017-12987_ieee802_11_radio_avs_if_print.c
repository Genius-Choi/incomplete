ieee802_11_radio_avs_if_print(netdissect_options *ndo,
                              const struct pcap_pkthdr *h, const u_char *p)
{
	return ieee802_11_avs_radio_print(ndo, p, h->len, h->caplen);
}
