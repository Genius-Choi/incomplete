void nci_clear_target_list(struct nci_dev *ndev)
{
	memset(ndev->targets, 0,
	       (sizeof(struct nfc_target)*NCI_MAX_DISCOVERED_TARGETS));

	ndev->n_targets = 0;
}
