static bool string_insn_completed(struct x86_emulate_ctxt *ctxt)
{
	/* The second termination condition only applies for REPE
	 * and REPNE. Test if the repeat string operation prefix is
	 * REPE/REPZ or REPNE/REPNZ and if it's the case it tests the
	 * corresponding termination condition according to:
	 * 	- if REPE/REPZ and ZF = 0 then done
	 * 	- if REPNE/REPNZ and ZF = 1 then done
	 */
	if (((ctxt->b == 0xa6) || (ctxt->b == 0xa7) ||
	     (ctxt->b == 0xae) || (ctxt->b == 0xaf))
	    && (((ctxt->rep_prefix == REPE_PREFIX) &&
		 ((ctxt->eflags & X86_EFLAGS_ZF) == 0))
		|| ((ctxt->rep_prefix == REPNE_PREFIX) &&
		    ((ctxt->eflags & X86_EFLAGS_ZF) == X86_EFLAGS_ZF))))
		return true;

	return false;
}
