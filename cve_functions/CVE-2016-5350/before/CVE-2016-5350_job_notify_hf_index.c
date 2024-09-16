job_notify_hf_index(int field)
{
	int result = -1;

	switch(field) {
	case JOB_NOTIFY_PRINTER_NAME:
		result = hf_printername;
		break;
	case JOB_NOTIFY_MACHINE_NAME:
		result = hf_machinename;
		break;
	case JOB_NOTIFY_PORT_NAME:
		result = hf_portname;
		break;
	case JOB_NOTIFY_USER_NAME:
		result = hf_username;
		break;
	case JOB_NOTIFY_NOTIFY_NAME:
		result = hf_notifyname;
		break;
	case JOB_NOTIFY_DATATYPE:
		result = hf_datatype;
		break;
	case JOB_NOTIFY_PRINT_PROCESSOR:
		result = hf_printprocessor;
		break;
	case JOB_NOTIFY_DRIVER_NAME:
		result = hf_drivername;
		break;
	case JOB_NOTIFY_DOCUMENT:
		result = hf_documentname;
		break;
	case JOB_NOTIFY_PRIORITY:
		result = hf_job_priority;
		break;
	case JOB_NOTIFY_POSITION:
		result = hf_job_position;
		break;
	case JOB_NOTIFY_TOTAL_PAGES:
		result = hf_job_totalpages;
		break;
	case JOB_NOTIFY_PAGES_PRINTED:
		result = hf_job_pagesprinted;
		break;
	case JOB_NOTIFY_TOTAL_BYTES:
		result = hf_job_totalbytes;
		break;
	case JOB_NOTIFY_BYTES_PRINTED:
		result = hf_job_bytesprinted;
		break;
	}

	return result;
}
