#include	<sys/select.h>
#include	"SelectUnix.hpp"

SelectUnix::SelectUnix()
{
}

SelectUnix::~SelectUnix()
{
}

bool		SelectUnix::call(const FDSet* read, const FDSet* write)
{
  fd_set*	new_read = (fd_set*)read->getFDSet();
  (void)write;
  struct timeval timeout;

  timeout.tv_sec = 0;
  timeout.tv_usec = 0;
  //FDSetUnix	*new_write = (FDSetUnix *)write->getFDSet();
  if (select(read->getHighFD() + 1, (fd_set*)new_read, NULL, NULL, &timeout) == -1)
    {
      return (false);
    }
  return (true);
}
