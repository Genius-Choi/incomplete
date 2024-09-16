struct pathname *process_extract_files(struct pathname *path, char *filename)
{
	FILE *fd;
	char buffer[MAX_LINE + 1]; /* overflow safe */
	char *name;

	fd = fopen(filename, "r");
	if(fd == NULL)
		EXIT_UNSQUASH("Failed to open extract file \"%s\" because %s\n",
			filename, strerror(errno));

	while(fgets(name = buffer, MAX_LINE + 1, fd) != NULL) {
		int len = strlen(name);

		if(len == MAX_LINE && name[len - 1] != '\n')
			/* line too large */
			EXIT_UNSQUASH("Line too long when reading "
				"extract file \"%s\", larger than %d "
				"bytes\n", filename, MAX_LINE);

		/*
		 * Remove '\n' terminator if it exists (the last line
		 * in the file may not be '\n' terminated)
		 */
		if(len && name[len - 1] == '\n')
			name[len - 1] = '\0';

		/* Skip any leading whitespace */
		while(isspace(*name))
			name ++;

		/* if comment line, skip */
		if(*name == '#')
			continue;

		/* check for initial backslash, to accommodate
		 * filenames with leading space or leading # character
		 */
		if(*name == '\\')
			name ++;

		/* if line is now empty after skipping characters, skip it */
		if(*name == '\0')
			continue;

		path = add_path(path, name, name);
	}

	if(ferror(fd))
		EXIT_UNSQUASH("Reading extract file \"%s\" failed because %s\n",
			filename, strerror(errno));

	fclose(fd);
	return path;
}
