static inline unsigned long idx_to_kaddr(struct xen_netbk *netbk,
					 u16 idx)
{
	return (unsigned long)pfn_to_kaddr(idx_to_pfn(netbk, idx));
}
