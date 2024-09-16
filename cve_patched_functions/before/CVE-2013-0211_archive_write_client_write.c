archive_write_client_write(struct archive_write_filter *f,
    const void *_buff, size_t length)
{
	struct archive_write *a = (struct archive_write *)f->archive;
        struct archive_none *state = (struct archive_none *)f->data;
	const char *buff = (const char *)_buff;
	ssize_t remaining, to_copy;
	ssize_t bytes_written;

	remaining = length;

	/*
	 * If there is no buffer for blocking, just pass the data
	 * straight through to the client write callback.  In
	 * particular, this supports "no write delay" operation for
	 * special applications.  Just set the block size to zero.
	 */
	if (state->buffer_size == 0) {
		while (remaining > 0) {
			bytes_written = (a->client_writer)(&a->archive,
			    a->client_data, buff, remaining);
			if (bytes_written <= 0)
				return (ARCHIVE_FATAL);
			remaining -= bytes_written;
			buff += bytes_written;
		}
		return (ARCHIVE_OK);
	}

	/* If the copy buffer isn't empty, try to fill it. */
	if (state->avail < state->buffer_size) {
		/* If buffer is not empty... */
		/* ... copy data into buffer ... */
		to_copy = ((size_t)remaining > state->avail) ?
			state->avail : (size_t)remaining;
		memcpy(state->next, buff, to_copy);
		state->next += to_copy;
		state->avail -= to_copy;
		buff += to_copy;
		remaining -= to_copy;
		/* ... if it's full, write it out. */
		if (state->avail == 0) {
			char *p = state->buffer;
			size_t to_write = state->buffer_size;
			while (to_write > 0) {
				bytes_written = (a->client_writer)(&a->archive,
				    a->client_data, p, to_write);
				if (bytes_written <= 0)
					return (ARCHIVE_FATAL);
				if ((size_t)bytes_written > to_write) {
					archive_set_error(&(a->archive),
					    -1, "write overrun");
					return (ARCHIVE_FATAL);
				}
				p += bytes_written;
				to_write -= bytes_written;
			}
			state->next = state->buffer;
			state->avail = state->buffer_size;
		}
	}

	while ((size_t)remaining >= state->buffer_size) {
		/* Write out full blocks directly to client. */
		bytes_written = (a->client_writer)(&a->archive,
		    a->client_data, buff, state->buffer_size);
		if (bytes_written <= 0)
			return (ARCHIVE_FATAL);
		buff += bytes_written;
		remaining -= bytes_written;
	}

	if (remaining > 0) {
		/* Copy last bit into copy buffer. */
		memcpy(state->next, buff, remaining);
		state->next += remaining;
		state->avail -= remaining;
	}
	return (ARCHIVE_OK);
}
