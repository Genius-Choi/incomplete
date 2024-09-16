GArray* parse_cfile(gchar* f, GError** e) {
	const char* DEFAULT_ERROR = "Could not parse %s in group %s: %s";
	const char* MISSING_REQUIRED_ERROR = "Could not find required value %s in group %s: %s";
	SERVER s;
	gchar *virtstyle=NULL;
	PARAM lp[] = {
		{ "exportname", TRUE,	PARAM_STRING, 	NULL, 0 },
		{ "port", 	TRUE,	PARAM_INT, 	NULL, 0 },
		{ "authfile",	FALSE,	PARAM_STRING,	NULL, 0 },
		{ "filesize",	FALSE,	PARAM_INT,	NULL, 0 },
		{ "virtstyle",	FALSE,	PARAM_STRING,	NULL, 0 },
		{ "prerun",	FALSE,	PARAM_STRING,	NULL, 0 },
		{ "postrun",	FALSE,	PARAM_STRING,	NULL, 0 },
		{ "readonly",	FALSE,	PARAM_BOOL,	NULL, F_READONLY },
		{ "multifile",	FALSE,	PARAM_BOOL,	NULL, F_MULTIFILE },
		{ "copyonwrite", FALSE,	PARAM_BOOL,	NULL, F_COPYONWRITE },
		{ "sparse_cow",	FALSE,	PARAM_BOOL,	NULL, F_SPARSE },
		{ "sdp",	FALSE,	PARAM_BOOL,	NULL, F_SDP },
		{ "sync",	FALSE,  PARAM_BOOL,	NULL, F_SYNC },
		{ "listenaddr", FALSE,  PARAM_STRING,   NULL, 0 },
		{ "maxconnections", FALSE, PARAM_INT,	NULL, 0 },
	};
	const int lp_size=sizeof(lp)/sizeof(PARAM);
	PARAM gp[] = {
		{ "user",	FALSE, PARAM_STRING,	&runuser,	0 },
		{ "group",	FALSE, PARAM_STRING,	&rungroup,	0 },
		{ "oldstyle",	FALSE, PARAM_BOOL,	&do_oldstyle,	1 },
		{ "listenaddr", FALSE, PARAM_STRING,	&modern_listen, 0 },
	};
	PARAM* p=gp;
	int p_size=sizeof(gp)/sizeof(PARAM);
	GKeyFile *cfile;
	GError *err = NULL;
	const char *err_msg=NULL;
	GQuark errdomain;
	GArray *retval=NULL;
	gchar **groups;
	gboolean value;
	gchar* startgroup;
	gint i;
	gint j;

	errdomain = g_quark_from_string("parse_cfile");
	cfile = g_key_file_new();
	retval = g_array_new(FALSE, TRUE, sizeof(SERVER));
	if(!g_key_file_load_from_file(cfile, f, G_KEY_FILE_KEEP_COMMENTS |
			G_KEY_FILE_KEEP_TRANSLATIONS, &err)) {
		g_set_error(e, errdomain, CFILE_NOTFOUND, "Could not open config file %s.", f);
		g_key_file_free(cfile);
		return retval;
	}
	startgroup = g_key_file_get_start_group(cfile);
	if(!startgroup || strcmp(startgroup, "generic")) {
		g_set_error(e, errdomain, CFILE_MISSING_GENERIC, "Config file does not contain the [generic] group!");
		g_key_file_free(cfile);
		return NULL;
	}
	groups = g_key_file_get_groups(cfile, NULL);
	for(i=0;groups[i];i++) {
		memset(&s, '\0', sizeof(SERVER));
		lp[0].target=&(s.exportname);
		lp[1].target=&(s.port);
		lp[2].target=&(s.authname);
		lp[3].target=&(s.expected_size);
		lp[4].target=&(virtstyle);
		lp[5].target=&(s.prerun);
		lp[6].target=&(s.postrun);
		lp[7].target=lp[8].target=lp[9].target=
				lp[10].target=lp[11].target=
				lp[12].target=&(s.flags);
		lp[13].target=&(s.listenaddr);
		lp[14].target=&(s.max_connections);

		/* After the [generic] group, start parsing exports */
		if(i==1) {
			p=lp;
			p_size=lp_size;
		} 
		for(j=0;j<p_size;j++) {
			g_assert(p[j].target != NULL);
			g_assert(p[j].ptype==PARAM_INT||p[j].ptype==PARAM_STRING||p[j].ptype==PARAM_BOOL);
			switch(p[j].ptype) {
				case PARAM_INT:
					*((gint*)p[j].target) =
						g_key_file_get_integer(cfile,
								groups[i],
								p[j].paramname,
								&err);
					break;
				case PARAM_STRING:
					*((gchar**)p[j].target) =
						g_key_file_get_string(cfile,
								groups[i],
								p[j].paramname,
								&err);
					break;
				case PARAM_BOOL:
					value = g_key_file_get_boolean(cfile,
							groups[i],
							p[j].paramname, &err);
					if(!err) {
						if(value) {
							*((gint*)p[j].target) |= p[j].flagval;
						} else {
							*((gint*)p[j].target) &= ~(p[j].flagval);
						}
					}
					break;
			}
			if(!strcmp(p[j].paramname, "port") && !strcmp(p[j].target, NBD_DEFAULT_PORT)) {
				g_set_error(e, errdomain, CFILE_INCORRECT_PORT, "Config file specifies default port for oldstyle export");
				g_key_file_free(cfile);
				return NULL;
			}
			if(err) {
				if(err->code == G_KEY_FILE_ERROR_KEY_NOT_FOUND) {
					if(!p[j].required) {
						/* Ignore not-found error for optional values */
						g_clear_error(&err);
						continue;
					} else {
						err_msg = MISSING_REQUIRED_ERROR;
					}
				} else {
					err_msg = DEFAULT_ERROR;
				}
				g_set_error(e, errdomain, CFILE_VALUE_INVALID, err_msg, p[j].paramname, groups[i], err->message);
				g_array_free(retval, TRUE);
				g_error_free(err);
				g_key_file_free(cfile);
				return NULL;
			}
		}
		if(virtstyle) {
			if(!strncmp(virtstyle, "none", 4)) {
				s.virtstyle=VIRT_NONE;
			} else if(!strncmp(virtstyle, "ipliteral", 9)) {
				s.virtstyle=VIRT_IPLIT;
			} else if(!strncmp(virtstyle, "iphash", 6)) {
				s.virtstyle=VIRT_IPHASH;
			} else if(!strncmp(virtstyle, "cidrhash", 8)) {
				s.virtstyle=VIRT_CIDR;
				if(strlen(virtstyle)<10) {
					g_set_error(e, errdomain, CFILE_VALUE_INVALID, "Invalid value %s for parameter virtstyle in group %s: missing length", virtstyle, groups[i]);
					g_array_free(retval, TRUE);
					g_key_file_free(cfile);
					return NULL;
				}
				s.cidrlen=strtol(virtstyle+8, NULL, 0);
			} else {
				g_set_error(e, errdomain, CFILE_VALUE_INVALID, "Invalid value %s for parameter virtstyle in group %s", virtstyle, groups[i]);
				g_array_free(retval, TRUE);
				g_key_file_free(cfile);
				return NULL;
			}
			if(s.port && !do_oldstyle) {
				g_warning("A port was specified, but oldstyle exports were not requested. This may not do what you expect.");
				g_warning("Please read 'man 5 nbd-server' and search for oldstyle for more info");
			}
		} else {
			s.virtstyle=VIRT_IPLIT;
		}
		/* Don't need to free this, it's not our string */
		virtstyle=NULL;
		/* Don't append values for the [generic] group */
		if(i>0) {
			s.socket_family = AF_UNSPEC;
			s.servename = groups[i];

			append_serve(&s, retval);
		} else {
			if(!do_oldstyle) {
				lp[1].required = 0;
			}
		}
#ifndef WITH_SDP
		if(s.flags & F_SDP) {
			g_set_error(e, errdomain, CFILE_VALUE_UNSUPPORTED, "This nbd-server was built without support for SDP, yet group %s uses it", groups[i]);
			g_array_free(retval, TRUE);
			g_key_file_free(cfile);
			return NULL;
		}
#endif
	}
	if(i==1) {
		g_set_error(e, errdomain, CFILE_NO_EXPORTS, "The config file does not specify any exports");
	}
	g_key_file_free(cfile);
	return retval;
}
