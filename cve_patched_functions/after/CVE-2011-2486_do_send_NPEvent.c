static int do_send_NPEvent(rpc_message_t *message, void *p_value)
{
  NPEvent *event = (NPEvent *)p_value;
  int error;

  if (event == NULL || !is_valid_NPEvent_type(event))
	return RPC_ERROR_MESSAGE_ARGUMENT_INVALID;

  if ((error = rpc_message_send_int32(message, event->type)) < 0)
	return error;

  switch (event->type) {
  case GraphicsExpose:
	if ((error = do_send_XGraphicsExposeEvent(message, event)) < 0)
	  return error;
	break;
  case FocusIn:
  case FocusOut:
	if ((error = do_send_XFocusChangeEvent(message, event)) < 0)
	  return error;
	break;
  case EnterNotify:
  case LeaveNotify:
	if ((error = do_send_XCrossingEvent(message, event)) < 0)
	  return error;
	break;
  case MotionNotify:
	if ((error = do_send_XMotionEvent(message, event)) < 0)
	  return error;
	break;
  case ButtonPress:
  case ButtonRelease:
	if ((error = do_send_XButtonEvent(message, event)) < 0)
	  return error;
	break;
  case KeyPress:
  case KeyRelease:
	if ((error = do_send_XKeyEvent(message, event)) < 0)
	  return error;
	break;
  default:
	return RPC_ERROR_GENERIC;
  }

  return RPC_ERROR_NO_ERROR;
}
