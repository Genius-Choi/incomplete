static void upnp_event_send(struct upnp_event_notify * obj)
{
	int i;

	syslog(LOG_DEBUG, "%s: sending event notify message to %s%s",
	       "upnp_event_send", obj->addrstr, obj->portstr);
	syslog(LOG_DEBUG, "%s: msg: %s",
	       "upnp_event_send", obj->buffer + obj->sent);
	i = send(obj->s, obj->buffer + obj->sent, obj->tosend - obj->sent, 0);
	if(i<0) {
		if(errno != EAGAIN && errno != EWOULDBLOCK && errno != EINTR) {
			syslog(LOG_NOTICE, "%s: send(%s%s): %m", "upnp_event_send",
			       obj->addrstr, obj->portstr);
			obj->state = EError;
			return;
		} else {
			/* EAGAIN or EWOULDBLOCK or EINTR : no data sent */
			i = 0;
		}
	}
	if(i != (obj->tosend - obj->sent))
		syslog(LOG_NOTICE, "%s: %d bytes send out of %d",
		       "upnp_event_send", i, obj->tosend - obj->sent);
	obj->sent += i;
	if(obj->sent == obj->tosend)
		obj->state = EWaitingForResponse;
}
