#ifndef CLIENT_H
# define CLIENT_H

# include "utils.h"

# define USAGE_CLIENT "Usage : ./client [server_PID] [STRING should be sent]"
# define ERROR_SEND_SIGNAL "Error : Fail to send signal to server"
# define TIMEOUT "Error : No response from server"
# define SUCCESE_EXIT "Exit : Successfully sent string to server"
# define UNMATCHED_SIGNL "Error : Received signal differ from sent one"

#endif
