static Sdb* Pe_r_bin_store_var(Var* var) {
	unsigned int i = 0;
	char key[20];
	Sdb* sdb = NULL;
	if (var) {
		sdb = sdb_new0 ();
		if (sdb) {
			for (; i < var->numOfValues; i++) {
				snprintf (key, 20, "%d", i);
				sdb_num_set (sdb, key, var->Value[i], 0);
			}
		}
	}
	return sdb;
}
