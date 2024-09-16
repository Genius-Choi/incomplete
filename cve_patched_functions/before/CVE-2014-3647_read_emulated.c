static int read_emulated(struct x86_emulate_ctxt *ctxt,
			 unsigned long addr, void *dest, unsigned size)
{
	int rc;
	struct read_cache *mc = &ctxt->mem_read;

	if (mc->pos < mc->end)
		goto read_cached;

	WARN_ON((mc->end + size) >= sizeof(mc->data));

	rc = ctxt->ops->read_emulated(ctxt, addr, mc->data + mc->end, size,
				      &ctxt->exception);
	if (rc != X86EMUL_CONTINUE)
		return rc;

	mc->end += size;

read_cached:
	memcpy(dest, mc->data + mc->pos, size);
	mc->pos += size;
	return X86EMUL_CONTINUE;
}
