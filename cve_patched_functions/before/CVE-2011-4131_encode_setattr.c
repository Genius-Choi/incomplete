static void encode_setattr(struct xdr_stream *xdr, const struct nfs_setattrargs *arg, const struct nfs_server *server, struct compound_hdr *hdr)
{
	__be32 *p;

	p = reserve_space(xdr, 4+NFS4_STATEID_SIZE);
	*p++ = cpu_to_be32(OP_SETATTR);
	xdr_encode_opaque_fixed(p, arg->stateid.data, NFS4_STATEID_SIZE);
	hdr->nops++;
	hdr->replen += decode_setattr_maxsz;
	encode_attrs(xdr, arg->iap, server);
}
