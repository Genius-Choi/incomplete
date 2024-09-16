static bool in_subsystem_list(const char *c)
{
	int i;

	for (i = 0; i < nr_subsystems; i++) {
		if (strcmp(c, subsystems[i]) == 0)
			return true;
	}

	return false;
}
