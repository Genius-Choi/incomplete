vrrp_vmac_xmit_base_handler(__attribute__((unused)) vector_t *strvec)
{
	vrrp_t *vrrp = LIST_TAIL_DATA(vrrp_data->vrrp);

	__set_bit(VRRP_VMAC_XMITBASE_BIT, &vrrp->vmac_flags);
}
