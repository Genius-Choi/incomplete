piv_find_obj_by_containerid(sc_card_t *card, const u8 * str)
{
	int i;

	LOG_FUNC_CALLED(card->ctx);
	sc_log(card->ctx, "str=0x%02X%02X\n", str[0], str[1]);

	for (i = 0; piv_objects[i].enumtag < PIV_OBJ_LAST_ENUM; i++) {
		if ( str[0] == piv_objects[i].containerid[0] && str[1] == piv_objects[i].containerid[1])
			LOG_FUNC_RETURN(card->ctx, i);
	}

	LOG_FUNC_RETURN(card->ctx, -1);
}
