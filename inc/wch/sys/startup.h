#if SYS_STARTUP

#pragma once

//------------------------------------------------------------------------------

void reset_handler(void);
void reset_entry(void);

void irq_entry(void);
void irq_entry_default(void);

//------------------------------------------------------------------------------

#endif  /* SYS_STARTUP */
