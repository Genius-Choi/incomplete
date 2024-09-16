static int do_recv_NPEvent(rpc_message_t *message, void *p_value)
{
  NPEvent *event = (NPEvent *)p_value;
  int32_t event_type;
  int error;

  if ((error = rpc_message_recv_int32(message, &event_type)) < 0)
	return error;
  memset(event, 0, sizeof(*event));
  event->type = event_type;

  switch (event->type) {
  case GraphicsExpose:
	if ((error = do_recv_XGraphicsExposeEvent(message, event)) < 0)
	  return error;
	break;
  case FocusIn:
  case FocusOut:
	if ((error = do_recv_XFocusChangeEvent(message, event)) < 0)
	  return error;
	break;
  case EnterNotify:
  case LeaveNotify:
	if ((error = do_recv_XCrossingEvent(message, event)) < 0)
	  return error;
	break;
  case MotionNotify:
	if ((error = do_recv_XMotionEvent(message, event)) < 0)
	  return error;
	break;
  case ButtonPress:
  case ButtonRelease:
	if ((error = do_recv_XButtonEvent(message, event)) < 0)
	  return error;
	break;
  case KeyPress:
  case KeyRelease:
	if ((error = do_recv_XKeyEvent(message, event)) < 0)
	  return error;
	break;
  default:
	return RPC_ERROR_GENERIC;
  }

  return RPC_ERROR_NO_ERROR;
}
