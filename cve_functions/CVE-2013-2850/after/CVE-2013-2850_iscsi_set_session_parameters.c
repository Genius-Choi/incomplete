void iscsi_set_session_parameters(
	struct iscsi_sess_ops *ops,
	struct iscsi_param_list *param_list,
	int leading)
{
	char *tmpptr;
	struct iscsi_param *param;

	pr_debug("----------------------------------------------------"
			"--------------\n");
	list_for_each_entry(param, &param_list->param_list, p_list) {
		if (!IS_PSTATE_ACCEPTOR(param) && !IS_PSTATE_PROPOSER(param))
			continue;
		if (!strcmp(param->name, INITIATORNAME)) {
			if (!param->value)
				continue;
			if (leading)
				snprintf(ops->InitiatorName,
						sizeof(ops->InitiatorName),
						"%s", param->value);
			pr_debug("InitiatorName:                %s\n",
				param->value);
		} else if (!strcmp(param->name, INITIATORALIAS)) {
			if (!param->value)
				continue;
			snprintf(ops->InitiatorAlias,
						sizeof(ops->InitiatorAlias),
						"%s", param->value);
			pr_debug("InitiatorAlias:               %s\n",
				param->value);
		} else if (!strcmp(param->name, TARGETNAME)) {
			if (!param->value)
				continue;
			if (leading)
				snprintf(ops->TargetName,
						sizeof(ops->TargetName),
						"%s", param->value);
			pr_debug("TargetName:                   %s\n",
				param->value);
		} else if (!strcmp(param->name, TARGETALIAS)) {
			if (!param->value)
				continue;
			snprintf(ops->TargetAlias, sizeof(ops->TargetAlias),
					"%s", param->value);
			pr_debug("TargetAlias:                  %s\n",
				param->value);
		} else if (!strcmp(param->name, TARGETPORTALGROUPTAG)) {
			ops->TargetPortalGroupTag =
				simple_strtoul(param->value, &tmpptr, 0);
			pr_debug("TargetPortalGroupTag:         %s\n",
				param->value);
		} else if (!strcmp(param->name, MAXCONNECTIONS)) {
			ops->MaxConnections =
				simple_strtoul(param->value, &tmpptr, 0);
			pr_debug("MaxConnections:               %s\n",
				param->value);
		} else if (!strcmp(param->name, INITIALR2T)) {
			ops->InitialR2T = !strcmp(param->value, YES);
			 pr_debug("InitialR2T:                   %s\n",
				param->value);
		} else if (!strcmp(param->name, IMMEDIATEDATA)) {
			ops->ImmediateData = !strcmp(param->value, YES);
			pr_debug("ImmediateData:                %s\n",
				param->value);
		} else if (!strcmp(param->name, MAXBURSTLENGTH)) {
			ops->MaxBurstLength =
				simple_strtoul(param->value, &tmpptr, 0);
			pr_debug("MaxBurstLength:               %s\n",
				param->value);
		} else if (!strcmp(param->name, FIRSTBURSTLENGTH)) {
			ops->FirstBurstLength =
				simple_strtoul(param->value, &tmpptr, 0);
			pr_debug("FirstBurstLength:             %s\n",
				param->value);
		} else if (!strcmp(param->name, DEFAULTTIME2WAIT)) {
			ops->DefaultTime2Wait =
				simple_strtoul(param->value, &tmpptr, 0);
			pr_debug("DefaultTime2Wait:             %s\n",
				param->value);
		} else if (!strcmp(param->name, DEFAULTTIME2RETAIN)) {
			ops->DefaultTime2Retain =
				simple_strtoul(param->value, &tmpptr, 0);
			pr_debug("DefaultTime2Retain:           %s\n",
				param->value);
		} else if (!strcmp(param->name, MAXOUTSTANDINGR2T)) {
			ops->MaxOutstandingR2T =
				simple_strtoul(param->value, &tmpptr, 0);
			pr_debug("MaxOutstandingR2T:            %s\n",
				param->value);
		} else if (!strcmp(param->name, DATAPDUINORDER)) {
			ops->DataPDUInOrder = !strcmp(param->value, YES);
			pr_debug("DataPDUInOrder:               %s\n",
				param->value);
		} else if (!strcmp(param->name, DATASEQUENCEINORDER)) {
			ops->DataSequenceInOrder = !strcmp(param->value, YES);
			pr_debug("DataSequenceInOrder:          %s\n",
				param->value);
		} else if (!strcmp(param->name, ERRORRECOVERYLEVEL)) {
			ops->ErrorRecoveryLevel =
				simple_strtoul(param->value, &tmpptr, 0);
			pr_debug("ErrorRecoveryLevel:           %s\n",
				param->value);
		} else if (!strcmp(param->name, SESSIONTYPE)) {
			ops->SessionType = !strcmp(param->value, DISCOVERY);
			pr_debug("SessionType:                  %s\n",
				param->value);
		} else if (!strcmp(param->name, RDMAEXTENSIONS)) {
			ops->RDMAExtensions = !strcmp(param->value, YES);
			pr_debug("RDMAExtensions:               %s\n",
				param->value);
		}
	}
	pr_debug("----------------------------------------------------"
			"--------------\n");

}
