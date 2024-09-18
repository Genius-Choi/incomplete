int main(int argc, char *argv[])
{
	int err = 0, r, c, long_optind = 0;
	int do_info = 0;
	int do_get_conf_entry = 0;
	int do_set_conf_entry = 0;
	int do_list_readers = 0;
	int do_list_drivers = 0;
	int do_list_files = 0;
	int do_send_apdu = 0;
	int do_print_atr = 0;
	int do_print_version = 0;
	int do_print_serial = 0;
	int do_print_name = 0;
	int do_list_algorithms = 0;
	int do_reset = 0;
	int action_count = 0;
	const char *opt_driver = NULL;
	const char *opt_conf_entry = NULL;
	const char *opt_reset_type = NULL;
	char **p;
	sc_context_param_t ctx_param;

	setbuf(stderr, NULL);
	setbuf(stdout, NULL);

	while (1) {
		c = getopt_long(argc, argv, "inlG:S:fr:vs:Dc:aw", options, &long_optind);
		if (c == -1)
			break;
		if (c == '?')
			util_print_usage_and_die(app_name, options, option_help, NULL);
		switch (c) {
		case 'i':
			do_info = 1;
			action_count++;
			break;
		case 'G':
			do_get_conf_entry = 1;
			opt_conf_entry = optarg;
			action_count++;
			break;
		case 'S':
			do_set_conf_entry = 1;
			opt_conf_entry = optarg;
			action_count++;
			break;
		case 'l':
			do_list_readers = 1;
			action_count++;
			break;
		case 'D':
			do_list_drivers = 1;
			action_count++;
			break;
		case 'f':
			do_list_files = 1;
			action_count++;
			break;
		case 's':
			p = (char **) realloc(opt_apdus,
					(opt_apdu_count + 1) * sizeof(char *));
			if (!p) {
				fprintf(stderr, "Not enough memory\n");
				err = 1;
				goto end;
			}
			opt_apdus = p;
			opt_apdus[opt_apdu_count] = optarg;
			do_send_apdu++;
			if (opt_apdu_count == 0)
				action_count++;
			opt_apdu_count++;
			break;
		case 'a':
			do_print_atr = 1;
			action_count++;
			break;
		case 'n':
			do_print_name = 1;
			action_count++;
			break;
		case 'r':
			opt_reader = optarg;
			break;
		case 'v':
			verbose++;
			break;
		case OPT_VERSION:
			do_print_version = 1;
			action_count++;
			break;
		case 'c':
			opt_driver = optarg;
			break;
		case 'w':
			opt_wait = 1;
			break;
		case OPT_SERIAL:
			do_print_serial = 1;
			action_count++;
			break;
		case OPT_LIST_ALG:
			do_list_algorithms = 1;
			action_count++;
			break;
		case OPT_RESET:
			do_reset = 1;
			opt_reset_type = optarg;
			action_count++;
			break;
		}
	}
	if (action_count == 0)
		util_print_usage_and_die(app_name, options, option_help, NULL);

	if (do_print_version)   {
		printf("%s\n", OPENSC_SCM_REVISION);
		action_count--;
	}

	if (do_info) {
		opensc_info();
		action_count--;
	}

	memset(&ctx_param, 0, sizeof(ctx_param));
	ctx_param.ver      = 0;
	ctx_param.app_name = app_name;

	r = sc_context_create(&ctx, &ctx_param);
	if (r) {
		fprintf(stderr, "Failed to establish context: %s\n", sc_strerror(r));
		return 1;
	}

	ctx->flags |= SC_CTX_FLAG_ENABLE_DEFAULT_DRIVER;

	if (verbose > 1) {
		ctx->debug = verbose;
		sc_ctx_log_to_file(ctx, "stderr");
	}

	if (do_get_conf_entry) {
		if ((err = opensc_get_conf_entry (opt_conf_entry)))
			goto end;
		action_count--;
	}
	if (do_set_conf_entry) {
		if ((err = opensc_set_conf_entry (opt_conf_entry)))
			goto end;
		action_count--;
	}
	if (do_list_readers) {
		if ((err = list_readers()))
			goto end;
		action_count--;
	}
	if (do_list_drivers) {
		if ((err = list_drivers()))
			goto end;
		action_count--;
	}
	if (action_count <= 0)
		goto end;

	if (opt_driver != NULL) {
		err = sc_set_card_driver(ctx, opt_driver);
		if (err) {
			fprintf(stderr, "Driver '%s' not found!\n", opt_driver);
			err = 1;
			goto end;
		}
	}

	err = util_connect_card_ex(ctx, &card, opt_reader, opt_wait, 0, verbose);
	if (err)
		goto end;

	if (do_print_atr) {
		if (verbose) {
			printf("Card ATR:\n");
			util_hex_dump_asc(stdout, card->atr.value, card->atr.len, -1);
		} else {
			char tmp[SC_MAX_ATR_SIZE*3];
			sc_bin_to_hex(card->atr.value, card->atr.len, tmp, sizeof(tmp) - 1, ':');
			fprintf(stdout,"%s\n",tmp);
		}
		action_count--;
	}
	if (do_print_serial) {
		if (verbose)
			printf("Card serial number:");
		print_serial(card);
		action_count--;
	}
	if (do_print_name) {
		if (verbose)
			printf("Card name: ");
		printf("%s\n", card->name);
		action_count--;
	}
	if (do_send_apdu) {
		if ((err = send_apdu()))
			goto end;
		action_count--;
	}

	if (do_list_files) {
		if ((err = list_files()))
			goto end;
		action_count--;
	}

	if (do_list_algorithms) {
		if ((err = list_algorithms()))
			goto end;
		action_count--;
	}

	if (do_reset) {
		if ((err = card_reset(opt_reset_type)))
			goto end;
		action_count--;
	}
end:
	if (card) {
		sc_disconnect_card(card);
	}
	if (ctx)
		sc_release_context(ctx);
	return err;
}
