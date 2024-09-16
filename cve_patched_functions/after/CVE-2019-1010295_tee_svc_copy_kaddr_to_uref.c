TEE_Result tee_svc_copy_kaddr_to_uref(uint32_t *uref, void *kaddr)
{
	uint32_t ref = tee_svc_kaddr_to_uref(kaddr);

	return tee_svc_copy_to_user(uref, &ref, sizeof(ref));
}
