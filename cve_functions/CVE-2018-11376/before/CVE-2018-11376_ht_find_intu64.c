static ut64 ht_find_intu64(SdbHash* ht, int key, bool* found) {
	ut64 *mvalue = (ut64 *)ht_find (ht, sdb_fmt ("%d", key), found);
	return *mvalue;
}
