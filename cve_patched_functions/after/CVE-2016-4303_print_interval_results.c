print_interval_results(struct iperf_test *test, struct iperf_stream *sp, cJSON *json_interval_streams)
{
    char ubuf[UNIT_LEN];
    char nbuf[UNIT_LEN];
    char cbuf[UNIT_LEN];
    double st = 0., et = 0.;
    struct iperf_interval_results *irp = NULL;
    double bandwidth, lost_percent;

    irp = TAILQ_LAST(&sp->result->interval_results, irlisthead); /* get last entry in linked list */
    if (irp == NULL) {
	iperf_err(test, "print_interval_results error: interval_results is NULL");
        return;
    }
    if (!test->json_output) {
	/* First stream? */
	if (sp == SLIST_FIRST(&test->streams)) {
	    /* It it's the first interval, print the header;
	    ** else if there's more than one stream, print the separator;
	    ** else nothing.
	    */
	    if (timeval_equals(&sp->result->start_time, &irp->interval_start_time)) {
		if (test->protocol->id == Ptcp) {
		    if (test->sender && test->sender_has_retransmits)
			iprintf(test, "%s", report_bw_retrans_cwnd_header);
		    else
			iprintf(test, "%s", report_bw_header);
		} else {
		    if (test->sender)
			iprintf(test, "%s", report_bw_udp_sender_header);
		    else
			iprintf(test, "%s", report_bw_udp_header);
		}
	    } else if (test->num_streams > 1)
		iprintf(test, "%s", report_bw_separator);
	}
    }

    unit_snprintf(ubuf, UNIT_LEN, (double) (irp->bytes_transferred), 'A');
    bandwidth = (double) irp->bytes_transferred / (double) irp->interval_duration;
    unit_snprintf(nbuf, UNIT_LEN, bandwidth, test->settings->unit_format);
    
    st = timeval_diff(&sp->result->start_time, &irp->interval_start_time);
    et = timeval_diff(&sp->result->start_time, &irp->interval_end_time);
    
    if (test->protocol->id == Ptcp) {
	if (test->sender && test->sender_has_retransmits) {
	    /* Interval, TCP with retransmits. */
	    if (test->json_output)
		cJSON_AddItemToArray(json_interval_streams, iperf_json_printf("socket: %d  start: %f  end: %f  seconds: %f  bytes: %d  bits_per_second: %f  retransmits: %d  snd_cwnd:  %d  omitted: %b", (int64_t) sp->socket, (double) st, (double) et, (double) irp->interval_duration, (int64_t) irp->bytes_transferred, bandwidth * 8, (int64_t) irp->interval_retrans, (int64_t) irp->snd_cwnd, irp->omitted));
	    else {
		unit_snprintf(cbuf, UNIT_LEN, irp->snd_cwnd, 'A');
		iprintf(test, report_bw_retrans_cwnd_format, sp->socket, st, et, ubuf, nbuf, irp->interval_retrans, cbuf, irp->omitted?report_omitted:"");
	    }
	} else {
	    /* Interval, TCP without retransmits. */
	    if (test->json_output)
		cJSON_AddItemToArray(json_interval_streams, iperf_json_printf("socket: %d  start: %f  end: %f  seconds: %f  bytes: %d  bits_per_second: %f  omitted: %b", (int64_t) sp->socket, (double) st, (double) et, (double) irp->interval_duration, (int64_t) irp->bytes_transferred, bandwidth * 8, irp->omitted));
	    else
		iprintf(test, report_bw_format, sp->socket, st, et, ubuf, nbuf, irp->omitted?report_omitted:"");
	}
    } else {
	/* Interval, UDP. */
	if (test->sender) {
	    if (test->json_output)
		cJSON_AddItemToArray(json_interval_streams, iperf_json_printf("socket: %d  start: %f  end: %f  seconds: %f  bytes: %d  bits_per_second: %f  packets: %d  omitted: %b", (int64_t) sp->socket, (double) st, (double) et, (double) irp->interval_duration, (int64_t) irp->bytes_transferred, bandwidth * 8, (int64_t) irp->interval_packet_count, irp->omitted));
	    else
		iprintf(test, report_bw_udp_sender_format, sp->socket, st, et, ubuf, nbuf, irp->interval_packet_count, irp->omitted?report_omitted:"");
	} else {
	    lost_percent = 100.0 * irp->interval_cnt_error / irp->interval_packet_count;
	    if (test->json_output)
		cJSON_AddItemToArray(json_interval_streams, iperf_json_printf("socket: %d  start: %f  end: %f  seconds: %f  bytes: %d  bits_per_second: %f  jitter_ms: %f  lost_packets: %d  packets: %d  lost_percent: %f  omitted: %b", (int64_t) sp->socket, (double) st, (double) et, (double) irp->interval_duration, (int64_t) irp->bytes_transferred, bandwidth * 8, (double) irp->jitter * 1000.0, (int64_t) irp->interval_cnt_error, (int64_t) irp->interval_packet_count, (double) lost_percent, irp->omitted));
	    else
		iprintf(test, report_bw_udp_format, sp->socket, st, et, ubuf, nbuf, irp->jitter * 1000.0, irp->interval_cnt_error, irp->interval_packet_count, lost_percent, irp->omitted?report_omitted:"");
	}
    }
}
