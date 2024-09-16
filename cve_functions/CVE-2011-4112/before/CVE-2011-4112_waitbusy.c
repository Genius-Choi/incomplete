static int waitbusy (struct airo_info *ai) {
	int delay = 0;
	while ((IN4500(ai, COMMAND) & COMMAND_BUSY) && (delay < 10000)) {
		udelay (10);
		if ((++delay % 20) == 0)
			OUT4500(ai, EVACK, EV_CLEARCOMMANDBUSY);
	}
	return delay < 10000;
}
