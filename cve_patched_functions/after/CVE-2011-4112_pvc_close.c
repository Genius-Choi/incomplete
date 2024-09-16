static int pvc_close(struct net_device *dev)
{
	pvc_device *pvc = dev->ml_priv;

	if (--pvc->open_count == 0) {
		hdlc_device *hdlc = dev_to_hdlc(pvc->frad);
		if (state(hdlc)->settings.lmi == LMI_NONE)
			pvc->state.active = 0;

		if (state(hdlc)->settings.dce) {
			state(hdlc)->dce_changed = 1;
			pvc->state.active = 0;
		}
	}
	return 0;
}
