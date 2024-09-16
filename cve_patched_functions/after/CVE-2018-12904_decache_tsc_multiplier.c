static void decache_tsc_multiplier(struct vcpu_vmx *vmx)
{
	vmx->current_tsc_ratio = vmx->vcpu.arch.tsc_scaling_ratio;
	vmcs_write64(TSC_MULTIPLIER, vmx->current_tsc_ratio);
}
