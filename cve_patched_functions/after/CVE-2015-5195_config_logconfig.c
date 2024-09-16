config_logconfig(
	config_tree *ptree
	)
{
	attr_val *	my_lc;

	my_lc = HEAD_PFIFO(ptree->logconfig);
	for (; my_lc != NULL; my_lc = my_lc->link) {
		switch (my_lc->attr) {

		case '+':
			ntp_syslogmask |= get_logmask(my_lc->value.s);
			break;

		case '-':
			ntp_syslogmask &= ~get_logmask(my_lc->value.s);
			break;

		case '=':
			ntp_syslogmask = get_logmask(my_lc->value.s);
			break;
		}
	}
}
