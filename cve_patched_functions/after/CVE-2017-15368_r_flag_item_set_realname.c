R_API void r_flag_item_set_realname(RFlagItem *item, const char *realname) {
	if (item) {
		if (item->name != item->realname) {
			free (item->realname);
		}
		item->realname = ISNULLSTR (realname) ? NULL : strdup (realname);
	}
}
