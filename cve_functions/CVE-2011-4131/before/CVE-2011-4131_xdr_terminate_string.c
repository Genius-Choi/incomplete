xdr_terminate_string(struct xdr_buf *buf, const u32 len)
{
	char *kaddr;

	kaddr = kmap_atomic(buf->pages[0], KM_USER0);
	kaddr[buf->page_base + len] = '\0';
	kunmap_atomic(kaddr, KM_USER0);
}
