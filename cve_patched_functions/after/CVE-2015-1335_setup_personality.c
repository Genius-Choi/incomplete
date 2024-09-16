static int setup_personality(int persona)
{
	#if HAVE_SYS_PERSONALITY_H
	if (persona == -1)
		return 0;

	if (personality(persona) < 0) {
		SYSERROR("failed to set personality to '0x%x'", persona);
		return -1;
	}

	INFO("set personality to '0x%x'", persona);
	#endif

	return 0;
}
