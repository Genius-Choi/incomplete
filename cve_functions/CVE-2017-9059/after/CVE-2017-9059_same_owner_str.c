same_owner_str(struct nfs4_stateowner *sop, struct xdr_netobj *owner)
{
	return (sop->so_owner.len == owner->len) &&
		0 == memcmp(sop->so_owner.data, owner->data, owner->len);
}
