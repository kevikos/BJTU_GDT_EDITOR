#ifndef		SELECTUNIX_HPP_
# define	SELECTUNIX_HPP_

# include	"ISelect.hpp"

class		SelectUnix : public ISelect
{
 public:

  SelectUnix();
  virtual ~SelectUnix();
	
    virtual bool	call(const FDSet* read, const FDSet* write, struct timeval *tv);
};


#endif		// !SELECTUNIX_HPP_
