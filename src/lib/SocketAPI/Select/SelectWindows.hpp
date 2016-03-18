#ifndef		SELECTWINDOWS_HPP_
# define	SELECTWINDOWS_HPP_

# include	<WinSock2.h>
# include	"ISelect.hpp"

class		SelectWindows : public ISelect
{
public:

    SelectWindows();
    virtual ~SelectWindows();

    virtual bool	call(const FDSet* read, const FDSet* write, struct timeval *tv);
};

#endif		// !SELECTWINDOWS_HPP_
