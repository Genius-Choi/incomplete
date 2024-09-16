vrrp_handle_bfd_event(bfd_event_t * evt)
{
	vrrp_tracked_bfd_t *vbfd;
	tracking_vrrp_t *tbfd;
	vrrp_t * vrrp;
	element e, e1;
	struct timeval time_now;
	struct timeval timer_tmp;
	uint32_t delivery_time;

	if (__test_bit(LOG_DETAIL_BIT, &debug)) {
		time_now = timer_now();
		timersub(&time_now, &evt->sent_time, &timer_tmp);
		delivery_time = timer_long(timer_tmp);
		log_message(LOG_INFO, "Received BFD event: instance %s is in"
			    " state %s (delivered in %i usec)",
			    evt->iname, BFD_STATE_STR(evt->state), delivery_time);
	}

	LIST_FOREACH(vrrp_data->vrrp_track_bfds, vbfd, e) {
		if (strcmp(vbfd->bname, evt->iname))
			continue;

		if ((vbfd->bfd_up && evt->state == BFD_STATE_UP) ||
		    (!vbfd->bfd_up && evt->state == BFD_STATE_DOWN))
			continue;

		vbfd->bfd_up = (evt->state == BFD_STATE_UP);

		LIST_FOREACH(vbfd->tracking_vrrp, tbfd, e1) {
			vrrp = tbfd->vrrp;

			log_message(LOG_INFO, "VRRP_Instance(%s) Tracked BFD"
				    " instance %s is %s", vrrp->iname, evt->iname, vbfd->bfd_up ? "UP" : "DOWN");

			if (tbfd->weight) {
				if (vbfd->bfd_up)
					vrrp->total_priority += abs(tbfd->weight);
				else
					vrrp->total_priority -= abs(tbfd->weight);
				vrrp_set_effective_priority(vrrp);

				continue;
			}

			if (vbfd->bfd_up)
				try_up_instance(vrrp, false);
			else
				down_instance(vrrp);
		}

		break;
	}
}
