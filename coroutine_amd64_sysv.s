.globl co_yield

.extern current_coroutine
.extern yield_next

co_yield:
  push rbp
  push rbx
  push r12
  push r13
  push r14
  push r15
  // We are free to use all registers now, except RSP of course
  mov rax, [current_coroutine + rip]
  mov [rax], rsp
  mov rbx, [yield_next + rip]
  mov [current_coroutine + rip], rbx
  mov rsp, [rbx]
  jmp co_resume

co_resume:
  pop r15
  pop r14
  pop r13
  pop r12
  pop rbx
  pop rbp
  ret

