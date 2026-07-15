// Declaração da função externa e mapeamento no array de syscalls
extern uint64 sys_getruntime(void);

// Dentro do array estático uint64 (*syscalls[]) (void):
[SYS_getruntime] sys_getruntime,
