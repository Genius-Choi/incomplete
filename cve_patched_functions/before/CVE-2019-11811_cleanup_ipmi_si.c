static void cleanup_ipmi_si(void)
{
	struct smi_info *e, *tmp_e;

	if (!initialized)
		return;

	ipmi_si_pci_shutdown();

	ipmi_si_parisc_shutdown();

	ipmi_si_platform_shutdown();

	mutex_lock(&smi_infos_lock);
	list_for_each_entry_safe(e, tmp_e, &smi_infos, link)
		cleanup_one_si(e);
	mutex_unlock(&smi_infos_lock);
}
