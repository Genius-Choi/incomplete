static int compareFileMem(const char *filename, const char *mem, int size) {
    int res;
    int fd;
    char bytes[4096];
    int idx = 0;
    struct stat info;

    if (update_results) {
        fd = open(filename, WR_FLAGS, 0644);
        if (fd < 0) {
	    fprintf(stderr, "failed to open %s for writing", filename);
            return(-1);
	}
        res = write(fd, mem, size);
        close(fd);
        return(res != size);
    }

    if (stat(filename, &info) < 0) {
        fprintf(stderr, "failed to stat %s\n", filename);
	return(-1);
    }
    if (info.st_size != size) {
        fprintf(stderr, "file %s is %ld bytes, result is %d bytes\n",
	        filename, (long) info.st_size, size);
        return(-1);
    }
    fd = open(filename, RD_FLAGS);
    if (fd < 0) {
	fprintf(stderr, "failed to open %s for reading", filename);
        return(-1);
    }
    while (idx < size) {
        res = read(fd, bytes, 4096);
	if (res <= 0)
	    break;
	if (res + idx > size)
	    break;
	if (memcmp(bytes, &mem[idx], res) != 0) {
	    int ix;
	    for (ix=0; ix<res; ix++)
		if (bytes[ix] != mem[idx+ix])
			break;
	    fprintf(stderr,"Compare error at position %d\n", idx+ix);
	    close(fd);
	    return(1);
	}
	idx += res;
    }
    close(fd);
    if (idx != size) {
	fprintf(stderr,"Compare error index %d, size %d\n", idx, size);
    }
    return(idx != size);
}
