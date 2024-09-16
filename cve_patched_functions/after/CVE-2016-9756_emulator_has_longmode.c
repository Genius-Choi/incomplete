static int emulator_has_longmode(struct x86_emulate_ctxt *ctxt)
{
	u32 eax, ebx, ecx, edx;

	eax = 0x80000001;
	ecx = 0;
	ctxt->ops->get_cpuid(ctxt, &eax, &ebx, &ecx, &edx);
	return edx & bit(X86_FEATURE_LM);
}
