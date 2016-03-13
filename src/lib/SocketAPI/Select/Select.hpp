#ifndef		SELECT_HPP_
# define	SELECT_HPP_

#include	"./FDSet/FDSet.hpp"

class		Select
{
public:

  Select();
  ~Select();

  static bool	call(const FDSet* read, const FDSet* write);
};

#endif		// !SELECT_HPP_
