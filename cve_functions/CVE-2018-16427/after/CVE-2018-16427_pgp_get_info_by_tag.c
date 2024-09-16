pgp_get_info_by_tag(sc_card_t *card, unsigned int tag)
{
	struct pgp_priv_data *priv = DRVDATA(card);
	struct do_info *info;

	for (info = priv->pgp_objects; (info != NULL) && (info->id > 0); info++)
		if (tag == info->id)
			return info;

	return NULL;
}
