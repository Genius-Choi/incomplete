static __printf(2, 3) void verbose(struct bpf_verifier_env *env,
				   const char *fmt, ...)
{
	struct bpf_verifer_log *log = &env->log;
	unsigned int n;
	va_list args;

	if (!log->level || !log->ubuf || bpf_verifier_log_full(log))
		return;

	va_start(args, fmt);
	n = vscnprintf(log->kbuf, BPF_VERIFIER_TMP_LOG_SIZE, fmt, args);
	va_end(args);

	WARN_ONCE(n >= BPF_VERIFIER_TMP_LOG_SIZE - 1,
		  "verifier log line truncated - local buffer too short\n");

	n = min(log->len_total - log->len_used - 1, n);
	log->kbuf[n] = '\0';

	if (!copy_to_user(log->ubuf + log->len_used, log->kbuf, n + 1))
		log->len_used += n;
	else
		log->ubuf = NULL;
}
