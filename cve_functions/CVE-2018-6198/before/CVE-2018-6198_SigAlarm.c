SigAlarm(SIGNAL_ARG)
{
    char *data;

    if (CurrentAlarm->sec > 0) {
	CurrentKey = -1;
	CurrentKeyData = NULL;
	CurrentCmdData = data = (char *)CurrentAlarm->data;
#ifdef USE_MOUSE
	if (use_mouse)
	    mouse_inactive();
#endif
	w3mFuncList[CurrentAlarm->cmd].func();
#ifdef USE_MOUSE
	if (use_mouse)
	    mouse_active();
#endif
	CurrentCmdData = NULL;
	if (CurrentAlarm->status == AL_IMPLICIT_ONCE) {
	    CurrentAlarm->sec = 0;
	    CurrentAlarm->status = AL_UNSET;
	}
	if (Currentbuf->event) {
	    if (Currentbuf->event->status != AL_UNSET)
		CurrentAlarm = Currentbuf->event;
	    else
		Currentbuf->event = NULL;
	}
	if (!Currentbuf->event)
	    CurrentAlarm = &DefaultAlarm;
	if (CurrentAlarm->sec > 0) {
	    mySignal(SIGALRM, SigAlarm);
	    alarm(CurrentAlarm->sec);
	}
    }
    SIGNAL_RETURN;
}
