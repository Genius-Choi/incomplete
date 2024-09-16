proto_reg_handoff_u3v(void)
{
    dissector_handle_t u3v_handle = NULL;
    dissector_handle_t u3v_descr_handle = NULL;

    u3v_handle = find_dissector("u3v");
    dissector_add_uint("usb.bulk", IF_CLASS_MISCELLANEOUS, u3v_handle);
    heur_dissector_add("usb.bulk", dissect_u3v_heur, "USB3Vision Protocol", "u3v", proto_u3v,HEURISTIC_ENABLE);
    u3v_descr_handle = create_dissector_handle(dissect_u3v_descriptors, proto_u3v);
    dissector_add_uint("usb.descriptor", IF_CLASS_MISCELLANEOUS, u3v_descr_handle);
}
