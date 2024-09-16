static inline void pvc_carrier(int on, pvc_device *pvc)
{
	if (on) {
		if (pvc->main)
			if (!netif_carrier_ok(pvc->main))
				netif_carrier_on(pvc->main);
		if (pvc->ether)
			if (!netif_carrier_ok(pvc->ether))
				netif_carrier_on(pvc->ether);
	} else {
		if (pvc->main)
			if (netif_carrier_ok(pvc->main))
				netif_carrier_off(pvc->main);
		if (pvc->ether)
			if (netif_carrier_ok(pvc->ether))
				netif_carrier_off(pvc->ether);
	}
}
