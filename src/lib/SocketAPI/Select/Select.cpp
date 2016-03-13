#include	<iostream>
#include	"Select.hpp"
#include	"ISelect.hpp"

#ifdef		WIN32
#include	"SelectWindows.hpp"
#else
#include	"SelectUnix.hpp"
#endif		// WIN32

Select::Select()
{
}

Select::~Select()
{
}

bool		Select::call(const FDSet* read, const FDSet* write)
{
  ISelect*	select;

#ifdef WIN32
  select = new SelectWindows;
#else
  select = new SelectUnix;
#endif // WIN
  if (select->call(read, write) == false)
    {
      std::cerr << "[ERROR] : ISelect::call failed." << std::endl;
      delete select;
      return (false);
    }
  delete select;
  return (true);
}
