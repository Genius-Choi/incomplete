static inline int assign_eip_far(struct x86_emulate_ctxt *ctxt, ulong dst,
			       int cs_l)
{
	switch (ctxt->op_bytes) {
	case 2:
		ctxt->_eip = (u16)dst;
		break;
	case 4:
		ctxt->_eip = (u32)dst;
		break;
	case 8:
		if ((cs_l && is_noncanonical_address(dst)) ||
		    (!cs_l && (dst & ~(u32)-1)))
			return emulate_gp(ctxt, 0);
		ctxt->_eip = dst;
		break;
	default:
		WARN(1, "unsupported eip assignment size\n");
	}
	return X86EMUL_CONTINUE;
}
