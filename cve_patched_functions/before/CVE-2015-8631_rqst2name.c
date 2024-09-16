rqst2name(struct svc_req *rqstp)
{

    if (rqstp->rq_cred.oa_flavor == RPCSEC_GSS)
        return rqstp->rq_clntname;
    else
        return rqstp->rq_clntcred;
}
