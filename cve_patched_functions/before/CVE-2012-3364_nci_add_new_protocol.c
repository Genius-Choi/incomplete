static int nci_add_new_protocol(struct nci_dev *ndev,
				struct nfc_target *target,
				__u8 rf_protocol,
				__u8 rf_tech_and_mode,
				void *params)
{
	struct rf_tech_specific_params_nfca_poll *nfca_poll;
	struct rf_tech_specific_params_nfcb_poll *nfcb_poll;
	struct rf_tech_specific_params_nfcf_poll *nfcf_poll;
	__u32 protocol;

	if (rf_protocol == NCI_RF_PROTOCOL_T2T)
		protocol = NFC_PROTO_MIFARE_MASK;
	else if (rf_protocol == NCI_RF_PROTOCOL_ISO_DEP)
		protocol = NFC_PROTO_ISO14443_MASK;
	else if (rf_protocol == NCI_RF_PROTOCOL_T3T)
		protocol = NFC_PROTO_FELICA_MASK;
	else
		protocol = 0;

	if (!(protocol & ndev->poll_prots)) {
		pr_err("the target found does not have the desired protocol\n");
		return -EPROTO;
	}

	if (rf_tech_and_mode == NCI_NFC_A_PASSIVE_POLL_MODE) {
		nfca_poll = (struct rf_tech_specific_params_nfca_poll *)params;

		target->sens_res = nfca_poll->sens_res;
		target->sel_res = nfca_poll->sel_res;
		target->nfcid1_len = nfca_poll->nfcid1_len;
		if (target->nfcid1_len > 0) {
			memcpy(target->nfcid1, nfca_poll->nfcid1,
			       target->nfcid1_len);
		}
	} else if (rf_tech_and_mode == NCI_NFC_B_PASSIVE_POLL_MODE) {
		nfcb_poll = (struct rf_tech_specific_params_nfcb_poll *)params;

		target->sensb_res_len = nfcb_poll->sensb_res_len;
		if (target->sensb_res_len > 0) {
			memcpy(target->sensb_res, nfcb_poll->sensb_res,
			       target->sensb_res_len);
		}
	} else if (rf_tech_and_mode == NCI_NFC_F_PASSIVE_POLL_MODE) {
		nfcf_poll = (struct rf_tech_specific_params_nfcf_poll *)params;

		target->sensf_res_len = nfcf_poll->sensf_res_len;
		if (target->sensf_res_len > 0) {
			memcpy(target->sensf_res, nfcf_poll->sensf_res,
			       target->sensf_res_len);
		}
	} else {
		pr_err("unsupported rf_tech_and_mode 0x%x\n", rf_tech_and_mode);
		return -EPROTO;
	}

	target->supported_protocols |= protocol;

	pr_debug("protocol 0x%x\n", protocol);

	return 0;
}
