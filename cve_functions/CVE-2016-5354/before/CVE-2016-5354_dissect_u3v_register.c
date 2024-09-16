dissect_u3v_register(guint64 addr, proto_tree *branch, tvbuff_t *tvb, gint offset, gint length, u3v_conv_info_t * u3v_conv_info)
{
    gint isABRM = FALSE, isSBRM = FALSE, isSIRM = FALSE,isEIRM = FALSE;
    /* check if this is the access to one of the base address registers */
    if ( addr < 0x10000 ) {
        isABRM = TRUE;
        switch (addr) {
        case U3V_ABRM_GENCP_VERSION:
            proto_tree_add_item(branch, hf_u3v_bootstrap_GenCP_Version, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            break;
        case U3V_ABRM_MANUFACTURER_NAME:
            if ( length <= 64 ) {
                proto_tree_add_item(branch, hf_u3v_bootstrap_Manufacturer_Name, tvb, offset, length, ENC_ASCII|ENC_NA);
            }
            break;
        case U3V_ABRM_MODEL_NAME:
            if ( length <= 64 ) {
                proto_tree_add_item(branch, hf_u3v_bootstrap_Model_Name, tvb, offset, length, ENC_ASCII|ENC_NA);
            }
            break;
        case U3V_ABRM_FAMILY_NAME:
            if ( length <= 64 ) {
                proto_tree_add_item(branch, hf_u3v_bootstrap_Family_Name, tvb, offset, length, ENC_ASCII|ENC_NA);
            }
            break;
        case U3V_ABRM_DEVICE_VERSION:
            if ( length <= 64 ) {
                proto_tree_add_item(branch, hf_u3v_bootstrap_Device_Version, tvb, offset, length, ENC_ASCII|ENC_NA);
            }
            break;
        case U3V_ABRM_MANUFACTURER_INFO:
            if ( length <= 64 ) {
                proto_tree_add_item(branch, hf_u3v_bootstrap_Manufacturer_Info, tvb, offset, length, ENC_ASCII|ENC_NA);
            }
            break;
        case U3V_ABRM_SERIAL_NUMBER:
            if ( length <= 64 ) {
                proto_tree_add_item(branch, hf_u3v_bootstrap_Serial_Number, tvb, offset, length, ENC_ASCII|ENC_NA);
            }
            break;
        case U3V_ABRM_USER_DEFINED_NAME:
            if ( length <= 64 ) {
                proto_tree_add_item(branch, hf_u3v_bootstrap_User_Defined_Name, tvb, offset, length, ENC_ASCII|ENC_NA);
            }
            break;
        case U3V_ABRM_DEVICE_CAPABILITY:
            proto_tree_add_item(branch, hf_u3v_bootstrap_Device_Capability, tvb, offset, 8, ENC_LITTLE_ENDIAN);
            break;
        case U3V_ABRM_MAXIMUM_DEVICE_RESPONSE_TIME:
            proto_tree_add_item(branch, hf_u3v_bootstrap_Maximum_Device_Response_Time, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            break;
        case U3V_ABRM_MANIFEST_TABLE_ADDRESS:
            proto_tree_add_item(branch, hf_u3v_bootstrap_Manifest_Table_Address, tvb, offset, 8, ENC_LITTLE_ENDIAN);
            break;
        case U3V_ABRM_SBRM_ADDRESS:
            proto_tree_add_item(branch, hf_u3v_bootstrap_SBRM_Address, tvb, offset, 8, ENC_LITTLE_ENDIAN);
            break;
        case U3V_ABRM_DEVICE_CONFIGURATION:
            proto_tree_add_item(branch, hf_u3v_bootstrap_Device_Configuration, tvb, offset, 8, ENC_LITTLE_ENDIAN);
            break;
        case U3V_ABRM_HEARTBEAT_TIMEOUT:
            proto_tree_add_item(branch, hf_u3v_bootstrap_Heartbeat_Timeout, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            break;
        case U3V_ABRM_MESSAGE_CHANNEL_CHANNEL_ID:
            proto_tree_add_item(branch, hf_u3v_bootstrap_Message_Channel_channel_id, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            break;
        case U3V_ABRM_TIMESTAMP:
            proto_tree_add_item(branch, hf_u3v_bootstrap_Timestamp, tvb, offset, 8, ENC_LITTLE_ENDIAN);
            break;
        case U3V_ABRM_TIMESTAMP_LATCH:
            proto_tree_add_item(branch, hf_u3v_bootstrap_Timestamp_Latch, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            break;
        case U3V_ABRM_TIMESTAMP_INCREMENT:
            proto_tree_add_item(branch, hf_u3v_bootstrap_Timestamp_Increment, tvb, offset, 8, ENC_LITTLE_ENDIAN);
            break;
        case U3V_ABRM_ACCESS_PRIVILEGE:
            proto_tree_add_item(branch, hf_u3v_bootstrap_Access_Privilege, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            break;
        case U3V_ABRM_PROTOCOL_ENDIANESS:
            proto_tree_add_item(branch, hf_u3v_bootstrap_Protocol_Endianess, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            break;
        case U3V_ABRM_IMPLEMENTATION_ENDIANESS:
            proto_tree_add_item(branch, hf_u3v_bootstrap_Implementation_Endianess, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            break;
        default:
            isABRM = FALSE;
            break;
        }
    }
    if ( u3v_conv_info->sbrm_addr != 0 &&  (addr >= u3v_conv_info->sbrm_addr)) {
        guint64 map_offset = addr - u3v_conv_info->sbrm_addr;
        isSBRM = TRUE;
        switch(map_offset) {
        case U3V_SBRM_U3V_VERSION:
            proto_tree_add_item(branch, hf_u3v_bootstrap_U3V_Version, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            break;
        case U3V_SBRM_U3VCP_CAPABILITY_REGISTER:
            proto_tree_add_item(branch, hf_u3v_bootstrap_U3VCP_Capability_Register, tvb, offset, 8, ENC_LITTLE_ENDIAN);
            break;
        case U3V_SBRM_U3VCP_CONFIGURATION_REGISTER:
            proto_tree_add_item(branch, hf_u3v_bootstrap_U3VCP_Configuration_Register, tvb, offset, 8, ENC_LITTLE_ENDIAN);
            break;
        case U3V_SBRM_MAXIMUM_COMMAND_TRANSFER_LENGTH:
            proto_tree_add_item(branch, hf_u3v_bootstrap_Maximum_Command_Transfer_Length, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            break;
        case U3V_SBRM_MAXIMUM_ACKNOWLEDGE_TRANSFER_LENGTH:
            proto_tree_add_item(branch, hf_u3v_bootstrap_Maximum_Acknowledge_Transfer_Length, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            break;
        case U3V_SBRM_NUMBER_OF_STREAM_CHANNELS:
            proto_tree_add_item(branch, hf_u3v_bootstrap_Number_of_Stream_Channels, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            break;
        case U3V_SBRM_SIRM_ADDRESS:
            proto_tree_add_item(branch, hf_u3v_bootstrap_SIRM_Address, tvb, offset, 8, ENC_LITTLE_ENDIAN);
            break;
        case U3V_SBRM_SIRM_LENGTH:
            proto_tree_add_item(branch, hf_u3v_bootstrap_SIRM_Length, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            break;
        case U3V_SBRM_EIRM_ADDRESS:
            proto_tree_add_item(branch, hf_u3v_bootstrap_EIRM_Address, tvb, offset, 8, ENC_LITTLE_ENDIAN);
            break;
        case U3V_SBRM_EIRM_LENGTH:
            proto_tree_add_item(branch, hf_u3v_bootstrap_EIRM_Length, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            break;
        case U3V_SBRM_IIDC2_ADDRESS:
            proto_tree_add_item(branch, hf_u3v_bootstrap_IIDC2_Address, tvb, offset, 8, ENC_LITTLE_ENDIAN);
            break;
        case U3V_SBRM_CURRENT_SPEED:
            proto_tree_add_item(branch, hf_u3v_bootstrap_Current_Speed, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            break;
        default:
            isSBRM = FALSE;
            break;
        }
    }
    if ( u3v_conv_info->sirm_addr != 0 &&  (addr >= u3v_conv_info->sirm_addr)) {
        guint64 map_offset = addr - u3v_conv_info->sirm_addr;
        isSIRM = TRUE;
        switch(map_offset) {
        case U3V_SIRM_SI_INFO:
            proto_tree_add_item(branch, hf_u3v_bootstrap_SI_Info, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            break;
        case U3V_SIRM_SI_CONTROL:
            proto_tree_add_item(branch, hf_u3v_bootstrap_SI_Control, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            break;
        case U3V_SIRM_SI_REQUIRED_PAYLOAD_SIZE:
            proto_tree_add_item(branch, hf_u3v_bootstrap_SI_Required_Payload_Size, tvb, offset, 8, ENC_LITTLE_ENDIAN);
            break;
        case U3V_SIRM_SI_REQUIRED_LEADER_SIZE:
            proto_tree_add_item(branch, hf_u3v_bootstrap_SI_Required_Leader_Size, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            break;
        case U3V_SIRM_SI_REQUIRED_TRAILER_SIZE:
            proto_tree_add_item(branch, hf_u3v_bootstrap_SI_Required_Trailer_Size, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            break;
        case U3V_SIRM_SI_MAXIMUM_LEADER_SIZE:
            proto_tree_add_item(branch, hf_u3v_bootstrap_SI_Maximum_Leader_Size, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            break;
        case U3V_SIRM_SI_PAYLOAD_TRANSFER_SIZE:
            proto_tree_add_item(branch, hf_u3v_bootstrap_SI_Payload_Transfer_Size, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            break;
        case U3V_SIRM_SI_PAYLOAD_TRANSFER_COUNT:
            proto_tree_add_item(branch, hf_u3v_bootstrap_SI_Payload_Transfer_Count, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            break;
        case U3V_SIRM_SI_PAYLOAD_FINAL_TRANSFER1_SIZE:
            proto_tree_add_item(branch, hf_u3v_bootstrap_SI_Payload_Final_Transfer1_Size, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            break;
        case U3V_SIRM_SI_PAYLOAD_FINAL_TRANSFER2_SIZE:
            proto_tree_add_item(branch, hf_u3v_bootstrap_SI_Payload_Final_Transfer2_Size, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            break;
        case U3V_SIRM_SI_MAXIMUM_TRAILER_SIZE:
            proto_tree_add_item(branch, hf_u3v_bootstrap_SI_Maximum_Trailer_Size, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            break;
        default:
            isSIRM = FALSE;
            break;
        }
    }
    if ( u3v_conv_info->eirm_addr != 0 &&  (addr >= u3v_conv_info->eirm_addr)) {
        guint64 map_offset = addr -u3v_conv_info->eirm_addr;
        isEIRM=TRUE;
        switch(map_offset) {
        case U3V_EIRM_EI_CONTROL:
            proto_tree_add_item(branch, hf_u3v_bootstrap_EI_Control, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            break;
        case U3V_EIRM_MAXIMUM_EVENT_TRANSFER_LENGTH:
            proto_tree_add_item(branch, hf_u3v_bootstrap_Maximum_Event_Transfer_Length, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            break;
        case U3V_EIRM_EVENT_TEST_CONTROL:
            proto_tree_add_item(branch, hf_u3v_bootstrap_Event_Test_Control, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            break;
        default:
            isEIRM = FALSE;
            break;
        }
    }
    if(isABRM || isSBRM || isSIRM || isEIRM ) {
        return 1;
    }
    return 0;
}
