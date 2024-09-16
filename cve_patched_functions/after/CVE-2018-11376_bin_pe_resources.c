static void bin_pe_resources(RCore *r, int mode) {
	Sdb *sdb = NULL;
	int index = 0;
	const char *pe_path = "bin/cur/info/pe_resource";
	if (!(sdb = sdb_ns_path (r->sdb, pe_path, 0))) {
		return;
	}
	if (IS_MODE_SET (mode)) {
		r_flag_space_set (r->flags, "resources");
	} else if (IS_MODE_RAD (mode)) {
		r_cons_printf ("fs resources\n");
	} else if (IS_MODE_JSON (mode)) {
		r_cons_printf ("[");
	}
	while (true) {
		const char *timestrKey = sdb_fmt ("resource.%d.timestr", index);
		const char *vaddrKey = sdb_fmt ("resource.%d.vaddr", index);
		const char *sizeKey  = sdb_fmt ("resource.%d.size", index);
		const char *typeKey  = sdb_fmt ("resource.%d.type", index);
		const char *languageKey = sdb_fmt ("resource.%d.language", index);
		const char *nameKey = sdb_fmt ("resource.%d.name", index);
		char *timestr = sdb_get (sdb, timestrKey, 0);
		if (!timestr) {
			break;
		}
		ut64 vaddr = sdb_num_get (sdb, vaddrKey, 0);
		int size = (int)sdb_num_get (sdb, sizeKey, 0);
		int name = (int)sdb_num_get (sdb, nameKey, 0);
		char *type = sdb_get (sdb, typeKey, 0);
		char *lang = sdb_get (sdb, languageKey, 0);

		if (IS_MODE_SET (mode)) {
			const char *name = sdb_fmt ("resource.%d", index);
			r_flag_set (r->flags, name, vaddr, size);
		} else if (IS_MODE_RAD (mode)) {
			r_cons_printf ("f resource.%d %d 0x%08"PFMT32x"\n", index, size, vaddr);
		} else if (IS_MODE_JSON (mode)) {
			r_cons_printf("%s{\"name\":%d,\"index\":%d, \"type\":\"%s\","
					"\"vaddr\":%"PFMT64d", \"size\":%d, \"lang\":\"%s\"}",
					index? ",": "", name, index, type, vaddr, size, lang);
		} else {
			char *humanSize = r_num_units (NULL, size);
			r_cons_printf ("Resource %d\n", index);
			r_cons_printf ("  name: %d\n", name);
			r_cons_printf ("  timestamp: %s\n", timestr);
			r_cons_printf ("  vaddr: 0x%08"PFMT64x"\n", vaddr);
			if (humanSize) {
				r_cons_printf ("  size: %s\n", humanSize);
			}
			r_cons_printf ("  type: %s\n", type);
			r_cons_printf ("  language: %s\n", lang);
			free (humanSize);
		}

		R_FREE (timestr);
		R_FREE (type);
		R_FREE (lang)

		index++;
	}
	if (IS_MODE_JSON (mode)) {
		r_cons_printf ("]");
	} else if (IS_MODE_RAD (mode)) {
		r_cons_printf ("fs *");
	}
}
