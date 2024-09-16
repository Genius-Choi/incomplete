static void vmx_free_vcpu_nested(struct kvm_vcpu *vcpu)
{
       struct vcpu_vmx *vmx = to_vmx(vcpu);
       int r;

       r = vcpu_load(vcpu);
       BUG_ON(r);
       vmx_switch_vmcs(vcpu, &vmx->vmcs01);
       free_nested(vmx);
       vcpu_put(vcpu);
}
