addenv(struct cgi_environment *env, const char *fmt, ...)
{
	size_t n, space;
	int truncated = 0;
	char *added;
	va_list ap;

	/* Calculate how much space is left in the buffer */
	space = (env->buflen - env->bufused);

	/* Calculate an estimate for the required space */
	n = strlen(fmt) + 2 + 128;

	do {
		if (space <= n) {
			/* Allocate new buffer */
			n = env->buflen + CGI_ENVIRONMENT_SIZE;
			added = (char *)mg_realloc_ctx(env->buf, n, env->conn->phys_ctx);
			if (!added) {
				/* Out of memory */
				mg_cry_internal(
				    env->conn,
				    "%s: Cannot allocate memory for CGI variable [%s]",
				    __func__,
				    fmt);
				return;
			}
			env->buf = added;
			env->buflen = n;
			space = (env->buflen - env->bufused);
		}

		/* Make a pointer to the free space int the buffer */
		added = env->buf + env->bufused;

		/* Copy VARIABLE=VALUE\0 string into the free space */
		va_start(ap, fmt);
		mg_vsnprintf(env->conn, &truncated, added, (size_t)space, fmt, ap);
		va_end(ap);

		/* Do not add truncated strings to the environment */
		if (truncated) {
			/* Reallocate the buffer */
			space = 0;
			n = 1;
		}
	} while (truncated);

	/* Calculate number of bytes added to the environment */
	n = strlen(added) + 1;
	env->bufused += n;

	/* Now update the variable index */
	space = (env->varlen - env->varused);
	if (space < 2) {
		mg_cry_internal(env->conn,
		                "%s: Cannot register CGI variable [%s]",
		                __func__,
		                fmt);
		return;
	}

	/* Append a pointer to the added string into the envp array */
	env->var[env->varused] = added;
	env->varused++;
}
