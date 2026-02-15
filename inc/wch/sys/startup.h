#if SYS_STARTUP

#pragma once

//------------------------------------------------------------------------------

void reset_handler(void);
void reset_entry(void);

void isr_default_entry(void);
void isr_entry(void);

//------------------------------------------------------------------------------

#endif  /* SYS_STARTUP */
