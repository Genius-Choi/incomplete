proto_register_u3v(void)
{
    static gint *ett[] = {
        &ett_u3v,
        &ett_u3v_cmd,
        &ett_u3v_flags,
        &ett_u3v_ack,
        &ett_u3v_payload_cmd,
        &ett_u3v_payload_ack,
        &ett_u3v_payload_ack_subtree,
        &ett_u3v_payload_cmd_subtree,
        &ett_u3v_bootstrap_fields,
        &ett_u3v_stream_leader,
        &ett_u3v_stream_trailer,
        &ett_u3v_stream_payload,
        &ett_u3v_device_info_descriptor,
        &ett_u3v_device_info_descriptor_speed_support,
        &ett_u3v_device_info_descriptor_gencp_version,
        &ett_u3v_device_info_descriptor_u3v_version,
    };

    proto_u3v = proto_register_protocol("USB 3 Vision", "U3V", "u3v");
    proto_register_field_array(proto_u3v, hf, array_length(hf));
    proto_register_subtree_array(ett, array_length(ett));
    register_dissector("u3v", dissect_u3v, proto_u3v);
}
