static inline int copy_user_to_fpregs_zeroing(void __user *buf, u64 xbv, int fx_only)
{
	if (use_xsave()) {
		if ((unsigned long)buf % 64 || fx_only) {
			u64 init_bv = xfeatures_mask & ~XFEATURE_MASK_FPSSE;
			copy_kernel_to_xregs(&init_fpstate.xsave, init_bv);
			return copy_user_to_fxregs(buf);
		} else {
			u64 init_bv = xfeatures_mask & ~xbv;
			if (unlikely(init_bv))
				copy_kernel_to_xregs(&init_fpstate.xsave, init_bv);
			return copy_user_to_xregs(buf, xbv);
		}
	} else if (use_fxsr()) {
		return copy_user_to_fxregs(buf);
	} else
		return copy_user_to_fregs(buf);
}
