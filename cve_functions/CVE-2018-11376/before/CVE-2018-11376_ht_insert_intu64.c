static bool ht_insert_intu64(SdbHash* ht, int key, ut64 value) {
	ut64 *mvalue = malloc (sizeof (ut64));
	if (!mvalue) {
		return false;
	}
	*mvalue = value;
	return ht_insert (ht, sdb_fmt ("%d", key), (void *)mvalue);
}
