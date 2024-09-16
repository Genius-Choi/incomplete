static int brcmf_dev_pno_clean(struct net_device *ndev)
{
	int ret;

	/* Disable pfn */
	ret = brcmf_fil_iovar_int_set(netdev_priv(ndev), "pfn", 0);
	if (ret == 0) {
		/* clear pfn */
		ret = brcmf_fil_iovar_data_set(netdev_priv(ndev), "pfnclear",
					       NULL, 0);
	}
	if (ret < 0)
		brcmf_err("failed code %d\n", ret);

	return ret;
}
