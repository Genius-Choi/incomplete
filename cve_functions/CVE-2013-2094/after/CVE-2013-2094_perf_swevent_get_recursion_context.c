int perf_swevent_get_recursion_context(void)
{
	struct swevent_htable *swhash = &__get_cpu_var(swevent_htable);

	return get_recursion_context(swhash->recursion);
}
