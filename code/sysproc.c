// Implementação da rotina da syscall no kernel
uint64
sys_getruntime(void)
{
  return myproc()->runtime;
}
