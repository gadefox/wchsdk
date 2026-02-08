#if SYS_INIT

#pragma once

//------------------------------------------------------------------------------
// Use clock security system, enabled by default.

#ifndef SYS_CLK_SEC
#define SYS_CLK_SEC  1
#endif  /* SYS_CLK_SEC */

//------------------------------------------------------------------------------

void sys_init(void);

#ifdef SYS_CONSTRUCTORS
void sys_constructors(void);
#endif  /* SYS_CONSTRUCTORS */

//------------------------------------------------------------------------------

#endif  /* SYS_INIT */
