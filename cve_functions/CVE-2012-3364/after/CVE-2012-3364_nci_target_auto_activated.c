static void nci_target_auto_activated(struct nci_dev *ndev,
				      struct nci_rf_intf_activated_ntf *ntf)
{
	struct nfc_target *target;
	int rc;

	target = &ndev->targets[ndev->n_targets];

	rc = nci_add_new_protocol(ndev, target, ntf->rf_protocol,
				  ntf->activation_rf_tech_and_mode,
				  &ntf->rf_tech_specific_params);
	if (rc)
		return;

	target->logical_idx = ntf->rf_discovery_id;
	ndev->n_targets++;

	pr_debug("logical idx %d, n_targets %d\n",
		 target->logical_idx, ndev->n_targets);

	nfc_targets_found(ndev->nfc_dev, ndev->targets, ndev->n_targets);
}
