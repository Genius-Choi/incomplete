fm_mgr_get_resp_error_str
(
	IN		fm_msg_ret_code_t err
)
{
	switch(err){
		case FM_RET_BAD_RET_LEN:
			return "Return data length invalid";
		case FM_RET_OK:
			return "Ok";
		case FM_RET_DT_NOT_SUPPORTED:
			return "Data type not supported";
		case FM_RET_ACT_NOT_SUPPORTED:
			return "Action not supported";
		case FM_RET_INVALID:
			return "Invalid";
		case FM_RET_BAD_LEN:
			return "Send data length invalid";
		case FM_RET_BUSY:
			return "Busy";
		case FM_RET_NOT_FOUND:
			return "Record not found";
		case FM_RET_NO_NEXT:
			return "No next instance";
		case FM_RET_NOT_MASTER:
			return "SM is not master";
		case FM_RET_NOSUCHOBJECT:
			return "SNMP Err: No such object";
		case FM_RET_NOSUCHINSTANCE:
			return "SNMP Err: No such instance";
		case FM_RET_ENDOFMIBVIEW:
			return "SNMP Err: End of view";
		case FM_RET_ERR_NOERROR:
			return "SNMP Err: No error";
		case FM_RET_ERR_TOOBIG:
			return "SNMP Err: Object too big";
		case FM_RET_ERR_NOSUCHNAME:
			return "SNMP Err: no such name";
		case FM_RET_ERR_BADVALUE:
			return "SNMP Err: Bad value";
		case FM_RET_ERR_READONLY:
			return "SNMP Err: Read only";
		case FM_RET_ERR_GENERR:
			return "SNMP Err: General Error";
		case FM_RET_ERR_NOACCESS:
			return "SNMP Err: No Access";
		case FM_RET_ERR_WRONGTYPE:
			return "SNMP Err: Wrong Type";
		case FM_RET_ERR_WRONGLENGTH:
			return "SNMP Err: Wrong length";
		case FM_RET_ERR_WRONGENCODING:
			return "SNMP Err: Wrong encoding";
		case FM_RET_ERR_WRONGVALUE:
			return "SNMP Err: Wrong Value";
		case FM_RET_ERR_NOCREATION:
			return "SNMP Err: No Creation";
		case FM_RET_ERR_INCONSISTENTVALUE:
			return "SNMP Err: Inconsistent value";
		case FM_RET_ERR_RESOURCEUNAVAILABLE:
			return "SNMP Err: Resource Unavailable";
		case FM_RET_ERR_COMMITFAILED:
			return "SNMP Err: Commit failed";
		case FM_RET_ERR_UNDOFAILED:
			return "SNMP Err: Undo failed";
		case FM_RET_ERR_AUTHORIZATIONERROR:
			return "SNMP Err: Authorization error";
		case FM_RET_ERR_NOTWRITABLE:
			return "SNMP Err: Not Writable";
		case FM_RET_TIMEOUT:
			return "SNMP Err: Timeout";
		case FM_RET_UNKNOWN_DT:
			return "Unknown Datatype";
		case FM_RET_END_OF_TABLE:
			return "End of Table";
		case FM_RET_INTERNAL_ERR:
			return "Internal Error";
		case FM_RET_CONX_CLOSED:
			return "Connection Closed";

	}

	return "Unknown code";
}
