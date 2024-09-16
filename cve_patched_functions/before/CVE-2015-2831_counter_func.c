static void *counter_func(void *arg){

  {
    set_pid_priority(0,SCHED_FIFO,sched_get_priority_min(SCHED_FIFO),"Unable to set SCHED_FIFO for %d (\"%s\"). (%s)", "the counter_func");
  }

  for(;;){
    counter++;
    if(verbose)
      print_error(stderr,"counter set to %d",counter);
    sleep(increasetime);
  }
  return NULL;
}
