#include <iostream>

int main(int ac, char **av)
{
  if (ac != 3)
    {
      std::cout << "./editor host port" << std::endl;
      return (0);
    }
}
