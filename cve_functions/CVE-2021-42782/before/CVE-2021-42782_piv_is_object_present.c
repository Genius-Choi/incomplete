static int piv_is_object_present(sc_card_t *card, u8 *ptr)
{
	piv_private_data_t * priv = PIV_DATA(card);
	int r = 0;
	int enumtag;

	enumtag = piv_find_obj_by_containerid(card, ptr);
	if (enumtag >= 0 && priv->obj_cache[enumtag].flags & PIV_OBJ_CACHE_NOT_PRESENT)
		r = 1;

	LOG_FUNC_RETURN(card->ctx, r);
}
