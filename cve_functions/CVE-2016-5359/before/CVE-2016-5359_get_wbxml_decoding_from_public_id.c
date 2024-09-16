static const wbxml_decoding *get_wbxml_decoding_from_public_id (guint32 public_id)
{
	const wbxml_decoding *map = NULL;

	DebugLog(("get_wbxml_decoding_from_public_id: public_id = %u\n",
		  public_id));
	if (public_id >= 2) {
		const wbxml_integer_list *item = well_known_public_id_list;

		while (item && item->public_id && item->map) {
			if (item->public_id == public_id) {
				map = item->map;
				break;
			}
			item++;
		}
	}
	return map;
}
