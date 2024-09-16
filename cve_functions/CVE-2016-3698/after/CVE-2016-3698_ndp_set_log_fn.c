void ndp_set_log_fn(struct ndp *ndp,
		    void (*log_fn)(struct ndp *ndp, int priority,
				   const char *file, int line, const char *fn,
				   const char *format, va_list args))
{
	ndp->log_fn = log_fn;
	dbg(ndp, "Custom logging function %p registered.", log_fn);
}
