static inline int qeth_mtu_is_valid(struct qeth_card *card, int mtu)
{
	switch (card->info.type) {
	case QETH_CARD_TYPE_OSD:
	case QETH_CARD_TYPE_OSM:
	case QETH_CARD_TYPE_OSX:
	case QETH_CARD_TYPE_IQD:
		return ((mtu >= 576) &&
			(mtu <= card->info.max_mtu));
	case QETH_CARD_TYPE_OSN:
	case QETH_CARD_TYPE_UNKNOWN:
	default:
		return 1;
	}
}
