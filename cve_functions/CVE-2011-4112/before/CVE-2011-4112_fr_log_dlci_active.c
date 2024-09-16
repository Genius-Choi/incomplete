static inline void fr_log_dlci_active(pvc_device *pvc)
{
	netdev_info(pvc->frad, "DLCI %d [%s%s%s]%s %s\n",
		    pvc->dlci,
		    pvc->main ? pvc->main->name : "",
		    pvc->main && pvc->ether ? " " : "",
		    pvc->ether ? pvc->ether->name : "",
		    pvc->state.new ? " new" : "",
		    !pvc->state.exist ? "deleted" :
		    pvc->state.active ? "active" : "inactive");
}
