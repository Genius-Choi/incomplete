std_checkRuleset_genErrMsg(__attribute__((unused)) modConfData_t *modConf, instanceConf_t *inst)
{
    errmsg.LogError(0, NO_ERRCODE, "imzmq3: ruleset '%s' for socket %s not found - "
                    "using default ruleset instead", inst->pszBindRuleset,
                    inst->description);
}
