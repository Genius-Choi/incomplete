get_realtime_priority(vector_t *strvec, const char *process)
{
	int min_priority;
	int max_priority;
	int priority;

	if (vector_size(strvec) < 2) {
		report_config_error(CONFIG_GENERAL_ERROR, "No %s process real-time priority specified", process);
		return -1;
	}

	min_priority = sched_get_priority_min(SCHED_RR);
	max_priority = sched_get_priority_max(SCHED_RR);

	if (!read_int_strvec(strvec, 1, &priority, INT_MIN, INT_MAX, true)) {
		report_config_error(CONFIG_GENERAL_ERROR, "%s process real-time priority '%s' invalid", process, FMT_STR_VSLOT(strvec, 1));
		return -1;
	}

	if (priority < min_priority) {
		report_config_error(CONFIG_GENERAL_ERROR, "%s process real-time priority %d less than minimum %d - setting to minimum", process, priority, min_priority);
		priority = min_priority;
	}
	else if (priority > max_priority) {
		report_config_error(CONFIG_GENERAL_ERROR, "%s process real-time priority %d greater than maximum %d - setting to maximum", process, priority, max_priority);
		priority = max_priority;
	}

	return priority;
}
