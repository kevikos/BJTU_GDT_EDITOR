#include	"SelectWindows.hpp"

SelectWindows::SelectWindows()
{
}

SelectWindows::~SelectWindows()
{
}

bool		SelectWindows::call(const FDSet* read, const FDSet* write, struct timeval *tv)
{
    fd_set*	new_read = (fd_set*)read->getFDSet();
    (void)write;

    if (select(0, (fd_set*)new_read, NULL, NULL, tv) == -1)
    {
	return (false);
    }
    return (true);
}
