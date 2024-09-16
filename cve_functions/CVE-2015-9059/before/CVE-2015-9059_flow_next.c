flow_next (int flow)
{
	switch(flow) {
	case FC_NONE:
		flow = FC_RTSCTS;
		break;
	case FC_RTSCTS:
		flow = FC_XONXOFF;
		break;
	case FC_XONXOFF:
		flow = FC_NONE;
		break;
	default:
		flow = FC_NONE;
		break;
	}

	return flow;
}
