static void read_mmx_reg(struct x86_emulate_ctxt *ctxt, u64 *data, int reg)
{
	ctxt->ops->get_fpu(ctxt);
	switch (reg) {
	case 0: asm("movq %%mm0, %0" : "=m"(*data)); break;
	case 1: asm("movq %%mm1, %0" : "=m"(*data)); break;
	case 2: asm("movq %%mm2, %0" : "=m"(*data)); break;
	case 3: asm("movq %%mm3, %0" : "=m"(*data)); break;
	case 4: asm("movq %%mm4, %0" : "=m"(*data)); break;
	case 5: asm("movq %%mm5, %0" : "=m"(*data)); break;
	case 6: asm("movq %%mm6, %0" : "=m"(*data)); break;
	case 7: asm("movq %%mm7, %0" : "=m"(*data)); break;
	default: BUG();
	}
	ctxt->ops->put_fpu(ctxt);
}
