static int oz_hcd_hub_control(struct usb_hcd *hcd, u16 req_type, u16 wvalue,
				u16 windex, char *buf, u16 wlength)
{
	int err = 0;

	switch (req_type) {
	case ClearHubFeature:
		oz_dbg(HUB, "ClearHubFeature: %d\n", req_type);
		break;
	case ClearPortFeature:
		err = oz_clear_port_feature(hcd, wvalue, windex);
		break;
	case GetHubDescriptor:
		oz_get_hub_descriptor(hcd, (struct usb_hub_descriptor *)buf);
		break;
	case GetHubStatus:
		oz_dbg(HUB, "GetHubStatus: req_type = 0x%x\n", req_type);
		put_unaligned(cpu_to_le32(0), (__le32 *)buf);
		break;
	case GetPortStatus:
		err = oz_get_port_status(hcd, windex, buf);
		break;
	case SetHubFeature:
		oz_dbg(HUB, "SetHubFeature: %d\n", req_type);
		break;
	case SetPortFeature:
		err = oz_set_port_feature(hcd, wvalue, windex);
		break;
	default:
		oz_dbg(HUB, "Other: %d\n", req_type);
		break;
	}
	return err;
}
