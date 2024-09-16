static size_t num_nl(char *file)
{
	FILE *fp;
	char buf[80];
	size_t len, num = 0;

	fp = fopen(file, "r");
	if (!fp)
		return 0;

	do {
		char *ptr = buf;

		len = fread(buf, sizeof(char), sizeof(buf) - 1, fp);
		if (len > 0) {
			buf[len] = 0;
			while ((ptr = strchr(ptr, '\n'))) {
				ptr++;
				num++;
			}
		}
	} while (len > 0);
	fclose(fp);

	return num;
}
