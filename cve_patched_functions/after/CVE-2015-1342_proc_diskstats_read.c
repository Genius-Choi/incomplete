static int proc_diskstats_read(char *buf, size_t size, off_t offset,
		struct fuse_file_info *fi)
{
	char dev_name[72];
	struct fuse_context *fc = fuse_get_context();
	struct file_info *d = (struct file_info *)fi->fh;
	char *cg;
	char *io_serviced_str = NULL, *io_merged_str = NULL, *io_service_bytes_str = NULL,
			*io_wait_time_str = NULL, *io_service_time_str = NULL;
	unsigned long read = 0, write = 0;
	unsigned long read_merged = 0, write_merged = 0;
	unsigned long read_sectors = 0, write_sectors = 0;
	unsigned long read_ticks = 0, write_ticks = 0;
	unsigned long ios_pgr = 0, tot_ticks = 0, rq_ticks = 0;
	unsigned long rd_svctm = 0, wr_svctm = 0, rd_wait = 0, wr_wait = 0;
	char *cache = d->buf;
	size_t cache_size = d->buflen;
	char *line = NULL;
	size_t linelen = 0, total_len = 0, rv = 0;
	unsigned int major = 0, minor = 0;
	int i = 0;
	FILE *f = NULL;

	if (offset){
		if (offset > d->size)
			return -EINVAL;
		if (!d->cached)
			return 0;
		int left = d->size - offset;
		total_len = left > size ? size: left;
		memcpy(buf, cache + offset, total_len);
		return total_len;
	}

	cg = get_pid_cgroup(fc->pid, "blkio");
	if (!cg)
		return read_file("/proc/diskstats", buf, size, d);

	if (!cgfs_get_value("blkio", cg, "blkio.io_serviced", &io_serviced_str))
		goto err;
	if (!cgfs_get_value("blkio", cg, "blkio.io_merged", &io_merged_str))
		goto err;
	if (!cgfs_get_value("blkio", cg, "blkio.io_service_bytes", &io_service_bytes_str))
		goto err;
	if (!cgfs_get_value("blkio", cg, "blkio.io_wait_time", &io_wait_time_str))
		goto err;
	if (!cgfs_get_value("blkio", cg, "blkio.io_service_time", &io_service_time_str))
		goto err;


	f = fopen("/proc/diskstats", "r");
	if (!f)
		goto err;

	while (getline(&line, &linelen, f) != -1) {
		size_t l;
		char *printme, lbuf[256];

		i = sscanf(line, "%u %u %71s", &major, &minor, dev_name);
		if(i == 3){
			get_blkio_io_value(io_serviced_str, major, minor, "Read", &read);
			get_blkio_io_value(io_serviced_str, major, minor, "Write", &write);
			get_blkio_io_value(io_merged_str, major, minor, "Read", &read_merged);
			get_blkio_io_value(io_merged_str, major, minor, "Write", &write_merged);
			get_blkio_io_value(io_service_bytes_str, major, minor, "Read", &read_sectors);
			read_sectors = read_sectors/512;
			get_blkio_io_value(io_service_bytes_str, major, minor, "Write", &write_sectors);
			write_sectors = write_sectors/512;

			get_blkio_io_value(io_service_time_str, major, minor, "Read", &rd_svctm);
			rd_svctm = rd_svctm/1000000;
			get_blkio_io_value(io_wait_time_str, major, minor, "Read", &rd_wait);
			rd_wait = rd_wait/1000000;
			read_ticks = rd_svctm + rd_wait;

			get_blkio_io_value(io_service_time_str, major, minor, "Write", &wr_svctm);
			wr_svctm =  wr_svctm/1000000;
			get_blkio_io_value(io_wait_time_str, major, minor, "Write", &wr_wait);
			wr_wait =  wr_wait/1000000;
			write_ticks = wr_svctm + wr_wait;

			get_blkio_io_value(io_service_time_str, major, minor, "Total", &tot_ticks);
			tot_ticks =  tot_ticks/1000000;
		}else{
			continue;
		}

		memset(lbuf, 0, 256);
		if (read || write || read_merged || write_merged || read_sectors || write_sectors || read_ticks || write_ticks) {
			snprintf(lbuf, 256, "%u       %u %s %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu\n",
				major, minor, dev_name, read, read_merged, read_sectors, read_ticks,
				write, write_merged, write_sectors, write_ticks, ios_pgr, tot_ticks, rq_ticks);
			printme = lbuf;
		} else
			continue;

		l = snprintf(cache, cache_size, "%s", printme);
		if (l < 0) {
			perror("Error writing to fuse buf");
			rv = 0;
			goto err;
		}
		if (l >= cache_size) {
			fprintf(stderr, "Internal error: truncated write to cache\n");
			rv = 0;
			goto err;
		}
		cache += l;
		cache_size -= l;
		total_len += l;
	}

	d->cached = 1;
	d->size = total_len;
	if (total_len > size ) total_len = size;
	memcpy(buf, d->buf, total_len);

	rv = total_len;
err:
	free(cg);
	if (f)
		fclose(f);
	free(line);
	free(io_serviced_str);
	free(io_merged_str);
	free(io_service_bytes_str);
	free(io_wait_time_str);
	free(io_service_time_str);
	return rv;
}
