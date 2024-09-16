static int encode_compound_hdr(struct xdr_stream *xdr, struct compound_hdr *hdr)
{
	__be32 *p;

	dprintk("encode_compound: tag=%.*s\n", (int)hdr->taglen, hdr->tag);
	BUG_ON(hdr->taglen > NFS4_MAXTAGLEN);
	RESERVE_SPACE(12+(XDR_QUADLEN(hdr->taglen)<<2));
	WRITE32(hdr->taglen);
	WRITEMEM(hdr->tag, hdr->taglen);
	WRITE32(NFS4_MINOR_VERSION);
	WRITE32(hdr->nops);
	return 0;
}
