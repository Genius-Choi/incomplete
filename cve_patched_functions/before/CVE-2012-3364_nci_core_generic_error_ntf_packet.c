static void nci_core_generic_error_ntf_packet(struct nci_dev *ndev,
					      struct sk_buff *skb)
{
	__u8 status = skb->data[0];

	pr_debug("status 0x%x\n", status);

	if (atomic_read(&ndev->state) == NCI_W4_HOST_SELECT) {
		/* Activation failed, so complete the request
		   (the state remains the same) */
		nci_req_complete(ndev, status);
	}
}
