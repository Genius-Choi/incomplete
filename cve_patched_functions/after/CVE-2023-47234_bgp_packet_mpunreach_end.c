void bgp_packet_mpunreach_end(struct stream *s, size_t attrlen_pnt)
{
	bgp_packet_mpattr_end(s, attrlen_pnt);
}
