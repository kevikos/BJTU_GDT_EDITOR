#include	<sys/select.h>
#include	"SelectUnix.hpp"

SelectUnix::SelectUnix()
{
}

SelectUnix::~SelectUnix()
{
}

bool		SelectUnix::call(const FDSet* read, const FDSet* write, struct timeval *tv)
{
    fd_set*	new_read = (fd_set*)read->getFDSet();
    (void)write;

    if (select(read->getHighFD() + 1, (fd_set*)new_read, NULL, NULL, tv) == -1)
    {
	return (false);
    }
    return (true);
}
