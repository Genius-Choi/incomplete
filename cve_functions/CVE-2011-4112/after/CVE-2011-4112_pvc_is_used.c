static inline int pvc_is_used(pvc_device *pvc)
{
	return pvc->main || pvc->ether;
}
