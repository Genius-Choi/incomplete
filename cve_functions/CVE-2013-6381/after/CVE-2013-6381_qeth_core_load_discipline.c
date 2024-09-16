int qeth_core_load_discipline(struct qeth_card *card,
		enum qeth_discipline_id discipline)
{
	int rc = 0;
	mutex_lock(&qeth_mod_mutex);
	switch (discipline) {
	case QETH_DISCIPLINE_LAYER3:
		card->discipline = try_then_request_module(
			symbol_get(qeth_l3_discipline), "qeth_l3");
		break;
	case QETH_DISCIPLINE_LAYER2:
		card->discipline = try_then_request_module(
			symbol_get(qeth_l2_discipline), "qeth_l2");
		break;
	}
	if (!card->discipline) {
		dev_err(&card->gdev->dev, "There is no kernel module to "
			"support discipline %d\n", discipline);
		rc = -EINVAL;
	}
	mutex_unlock(&qeth_mod_mutex);
	return rc;
}
