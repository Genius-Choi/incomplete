int pm_restore_priority(p_fm_config_conx_hdlt hdl, fm_mgr_type_t mgr, int argc, char *argv[]) {
	fprintf(stderr, "pmRestorePriority:\n");
	fprintf(stderr, "\tThis command is not supported any more.  The priority of the\n");
	fprintf(stderr, "\tPerformance Manager(PM) is now based on the priority of the\n");
	fprintf(stderr, "\tSubnet manager(SM).  Use the smRestorePriority command\n");
	fprintf(stderr, "\tfor restoring the priority of the SM and PM.\n");
	return 0;
}
