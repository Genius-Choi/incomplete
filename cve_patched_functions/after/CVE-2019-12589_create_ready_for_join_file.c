static FILE *create_ready_for_join_file(void) {
	FILE *fp = fopen(RUN_READY_FOR_JOIN, "wxe");
	if (fp) {
		ASSERT_PERMS_STREAM(fp, 0, 0, 0644);
		return fp;
	}
	else {
		fprintf(stderr, "Error: cannot create %s\n", RUN_READY_FOR_JOIN);
		exit(1);
	}
}
