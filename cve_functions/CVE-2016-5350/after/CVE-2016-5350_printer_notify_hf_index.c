printer_notify_hf_index(int field)
{
	int result = -1;

	switch(field) {
	case PRINTER_NOTIFY_SERVER_NAME:
		result = hf_servername;
		break;
	case PRINTER_NOTIFY_PRINTER_NAME:
		result = hf_printername;
		break;
	case PRINTER_NOTIFY_SHARE_NAME:
		result = hf_sharename;
		break;
	case PRINTER_NOTIFY_PORT_NAME:
		result = hf_portname;
		break;
	case PRINTER_NOTIFY_DRIVER_NAME:
		result = hf_drivername;
		break;
	case PRINTER_NOTIFY_COMMENT:
		result = hf_printercomment;
		break;
	case PRINTER_NOTIFY_LOCATION:
		result = hf_printerlocation;
		break;
	case PRINTER_NOTIFY_SEPFILE:
		result = hf_sepfile;
		break;
	case PRINTER_NOTIFY_PRINT_PROCESSOR:
		result = hf_printprocessor;
		break;
	case PRINTER_NOTIFY_PARAMETERS:
		result = hf_parameters;
		break;
	case PRINTER_NOTIFY_DATATYPE:
		result = hf_parameters;
		break;
	}

	return result;
}
