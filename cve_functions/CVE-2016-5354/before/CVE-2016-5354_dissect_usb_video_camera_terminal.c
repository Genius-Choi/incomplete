dissect_usb_video_camera_terminal(proto_tree *tree, tvbuff_t *tvb, int offset)
{
    static const int *control_bits[] = {
        &hf_usb_vid_cam_control_D[0],
        &hf_usb_vid_cam_control_D[1],
        &hf_usb_vid_cam_control_D[2],
        &hf_usb_vid_cam_control_D[3],
        &hf_usb_vid_cam_control_D[4],
        &hf_usb_vid_cam_control_D[5],
        &hf_usb_vid_cam_control_D[6],
        &hf_usb_vid_cam_control_D[7],
        &hf_usb_vid_cam_control_D[8],
        &hf_usb_vid_cam_control_D[9],
        &hf_usb_vid_cam_control_D[10],
        &hf_usb_vid_cam_control_D[11],
        &hf_usb_vid_cam_control_D[12],
        &hf_usb_vid_cam_control_D[13],
        &hf_usb_vid_cam_control_D[14],
        &hf_usb_vid_cam_control_D[15],
        &hf_usb_vid_cam_control_D[16],
        &hf_usb_vid_cam_control_D[17],
        &hf_usb_vid_cam_control_D[18],
        &hf_usb_vid_cam_control_D[19],
        &hf_usb_vid_cam_control_D[20],
        &hf_usb_vid_cam_control_D[21],
        NULL
    };

    DISSECTOR_ASSERT(array_length(control_bits) == (1+array_length(hf_usb_vid_cam_control_D)));

    proto_tree_add_item(tree, hf_usb_vid_cam_objective_focal_len_min,  tvb, offset, 2, ENC_LITTLE_ENDIAN);
    offset += 2;
    proto_tree_add_item(tree, hf_usb_vid_cam_objective_focal_len_max,  tvb, offset, 2, ENC_LITTLE_ENDIAN);
    offset += 2;
    proto_tree_add_item(tree, hf_usb_vid_cam_ocular_focal_len, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    offset += 2;

    offset = dissect_bmControl(tree, tvb, offset, ett_camera_controls, control_bits);

    return offset;
}
