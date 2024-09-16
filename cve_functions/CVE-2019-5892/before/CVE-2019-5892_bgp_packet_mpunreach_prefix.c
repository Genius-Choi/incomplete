void bgp_packet_mpunreach_prefix(struct stream *s, struct prefix *p, afi_t afi,
				 safi_t safi, struct prefix_rd *prd,
				 mpls_label_t *label, uint32_t num_labels,
				 int addpath_encode, uint32_t addpath_tx_id,
				 struct attr *attr)
{
	uint8_t wlabel[3] = {0x80, 0x00, 0x00};

	if (safi == SAFI_LABELED_UNICAST) {
		label = (mpls_label_t *)wlabel;
		num_labels = 1;
	}

	bgp_packet_mpattr_prefix(s, afi, safi, p, prd, label, num_labels,
				 addpath_encode, addpath_tx_id, attr);
}
