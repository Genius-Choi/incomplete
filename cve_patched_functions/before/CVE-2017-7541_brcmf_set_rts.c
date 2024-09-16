static s32 brcmf_set_rts(struct net_device *ndev, u32 rts_threshold)
{
	s32 err = 0;

	err = brcmf_fil_iovar_int_set(netdev_priv(ndev), "rtsthresh",
				      rts_threshold);
	if (err)
		brcmf_err("Error (%d)\n", err);

	return err;
}
