#if SYS_INIT

#pragma once

//------------------------------------------------------------------------------

void sys_init(void);

#if SYS_CONSTR
void sys_call_constr(void);
#endif  /* SYS_CONSTR */

//------------------------------------------------------------------------------

#endif  /* SYS_INIT */
