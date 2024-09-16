static inline void delete_unused_pvcs(hdlc_device *hdlc)
{
	pvc_device **pvc_p = &state(hdlc)->first_pvc;

	while (*pvc_p) {
		if (!pvc_is_used(*pvc_p)) {
			pvc_device *pvc = *pvc_p;
#ifdef DEBUG_PVC
			printk(KERN_DEBUG "freeing unused pvc: %p\n", pvc);
#endif
			*pvc_p = pvc->next;
			kfree(pvc);
			continue;
		}
		pvc_p = &(*pvc_p)->next;
	}
}
