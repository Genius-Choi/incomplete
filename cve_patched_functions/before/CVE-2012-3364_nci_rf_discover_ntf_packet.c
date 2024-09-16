static void nci_rf_discover_ntf_packet(struct nci_dev *ndev,
				       struct sk_buff *skb)
{
	struct nci_rf_discover_ntf ntf;
	__u8 *data = skb->data;
	bool add_target = true;

	ntf.rf_discovery_id = *data++;
	ntf.rf_protocol = *data++;
	ntf.rf_tech_and_mode = *data++;
	ntf.rf_tech_specific_params_len = *data++;

	pr_debug("rf_discovery_id %d\n", ntf.rf_discovery_id);
	pr_debug("rf_protocol 0x%x\n", ntf.rf_protocol);
	pr_debug("rf_tech_and_mode 0x%x\n", ntf.rf_tech_and_mode);
	pr_debug("rf_tech_specific_params_len %d\n",
		 ntf.rf_tech_specific_params_len);

	if (ntf.rf_tech_specific_params_len > 0) {
		switch (ntf.rf_tech_and_mode) {
		case NCI_NFC_A_PASSIVE_POLL_MODE:
			data = nci_extract_rf_params_nfca_passive_poll(ndev,
				&(ntf.rf_tech_specific_params.nfca_poll), data);
			break;

		case NCI_NFC_B_PASSIVE_POLL_MODE:
			data = nci_extract_rf_params_nfcb_passive_poll(ndev,
				&(ntf.rf_tech_specific_params.nfcb_poll), data);
			break;

		case NCI_NFC_F_PASSIVE_POLL_MODE:
			data = nci_extract_rf_params_nfcf_passive_poll(ndev,
				&(ntf.rf_tech_specific_params.nfcf_poll), data);
			break;

		default:
			pr_err("unsupported rf_tech_and_mode 0x%x\n",
			       ntf.rf_tech_and_mode);
			data += ntf.rf_tech_specific_params_len;
			add_target = false;
		}
	}

	ntf.ntf_type = *data++;
	pr_debug("ntf_type %d\n", ntf.ntf_type);

	if (add_target == true)
		nci_add_new_target(ndev, &ntf);

	if (ntf.ntf_type == NCI_DISCOVER_NTF_TYPE_MORE) {
		atomic_set(&ndev->state, NCI_W4_ALL_DISCOVERIES);
	} else {
		atomic_set(&ndev->state, NCI_W4_HOST_SELECT);
		nfc_targets_found(ndev->nfc_dev, ndev->targets,
				  ndev->n_targets);
	}
}
