notify_script_compare(notify_script_t *a, notify_script_t *b)
{
	int i;

	if (a->num_args != b->num_args)
		return false;
	for (i = 0; i < a->num_args; i++) {
		if (strcmp(a->args[i], b->args[i]))
			return false;
	}

	return true;
}
