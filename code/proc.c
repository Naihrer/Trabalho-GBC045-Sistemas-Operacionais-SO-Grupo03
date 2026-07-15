// Modificação realizada na função scheduler(void) para o algoritmo SJF
struct proc *shortest_job = 0;
uint64 min_runtime = 0xffffffffffffffff;

for(p = proc; p < &proc[NPROC]; p++) {
    acquire(&p->lock);
    if(p->state == RUNNABLE) {
        if(p->runtime < min_runtime) {
            min_runtime = p->runtime;
            shortest_job = p;
        }
    }
    release(&p->lock);
}

if(shortest_job != 0){
    acquire(&shortest_job->lock);
    if(shortest_job->state == RUNNABLE) {
        shortest_job->state = RUNNING;
        c->proc = shortest_job;
        swtch(&c->context, &shortest_job->context);
        c->proc = 0;
    }
    release(&shortest_job->lock);
}
