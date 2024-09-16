int __init iriap_init(void)
{
	struct ias_object *obj;
	struct iriap_cb *server;
	__u8 oct_seq[6];
	__u16 hints;

	/* Allocate master array */
	iriap = hashbin_new(HB_LOCK);
	if (!iriap)
		return -ENOMEM;

	/* Object repository - defined in irias_object.c */
	irias_objects = hashbin_new(HB_LOCK);
	if (!irias_objects) {
		IRDA_WARNING("%s: Can't allocate irias_objects hashbin!\n",
			     __func__);
		hashbin_delete(iriap, NULL);
		return -ENOMEM;
	}

	/*
	 *  Register some default services for IrLMP
	 */
	hints  = irlmp_service_to_hint(S_COMPUTER);
	service_handle = irlmp_register_service(hints);

	/* Register the Device object with LM-IAS */
	obj = irias_new_object("Device", IAS_DEVICE_ID);
	irias_add_string_attrib(obj, "DeviceName", "Linux", IAS_KERNEL_ATTR);

	oct_seq[0] = 0x01;  /* Version 1 */
	oct_seq[1] = 0x00;  /* IAS support bits */
	oct_seq[2] = 0x00;  /* LM-MUX support bits */
#ifdef CONFIG_IRDA_ULTRA
	oct_seq[2] |= 0x04; /* Connectionless Data support */
#endif
	irias_add_octseq_attrib(obj, "IrLMPSupport", oct_seq, 3,
				IAS_KERNEL_ATTR);
	irias_insert_object(obj);

	/*
	 *  Register server support with IrLMP so we can accept incoming
	 *  connections
	 */
	server = iriap_open(LSAP_IAS, IAS_SERVER, NULL, NULL);
	if (!server) {
		IRDA_DEBUG(0, "%s(), unable to open server\n", __func__);
		return -1;
	}
	iriap_register_lsap(server, LSAP_IAS, IAS_SERVER);

	return 0;
}
