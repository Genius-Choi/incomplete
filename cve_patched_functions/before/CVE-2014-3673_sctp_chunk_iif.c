int sctp_chunk_iif(const struct sctp_chunk *chunk)
{
	struct sctp_af *af;
	int iif = 0;

	af = sctp_get_af_specific(ipver2af(ip_hdr(chunk->skb)->version));
	if (af)
		iif = af->skb_iif(chunk->skb);

	return iif;
}
