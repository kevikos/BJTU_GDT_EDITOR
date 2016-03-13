#include	"SelectWindows.hpp"

SelectWindows::SelectWindows()
{
}

SelectWindows::~SelectWindows()
{
}

bool		SelectWindows::call(const FDSet* read, const FDSet* write)
{
  fd_set*	new_read = (fd_set*)read->getFDSet();
  struct timeval tv;

  tv.tv_sec = 0;
  tv.tv_usec = 0;
  //FDSetWindows	*new_write = (FDSetWindows *)write->getFDSet();
  if (select(0, (fd_set*)new_read, NULL, NULL, &tv) == -1)
    {
      return (false);
    }
  return (true);
}
