static Sdb* Pe_r_bin_store_string_table(StringTable* stringTable) {
	char key[20];
	char* encodedKey = NULL;
	int i = 0;
	Sdb* sdb = NULL;
	if (!stringTable) {
		return NULL;
	}
	sdb = sdb_new0 ();
	if (!sdb) {
		return NULL;
	}
	encodedKey = sdb_encode ((unsigned char*) stringTable->szKey, EIGHT_HEX_DIG_UTF_16_LEN);
	if (!encodedKey) {
		sdb_free (sdb);
		return NULL;
	}
	sdb_set (sdb, "key", encodedKey, 0);
	free (encodedKey);
	for (; i < stringTable->numOfChildren; i++) {
		snprintf (key, 20, "string%d", i);
		sdb_ns_set (sdb, key, Pe_r_bin_store_string (stringTable->Children[i]));
	}
	return sdb;
}
