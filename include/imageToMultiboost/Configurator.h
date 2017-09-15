#include <types.hpp>

class Configurator
{
public:
  Configurator();
  virtual ~Configurator() = default;
  Config parse(std::string configFilePath);

  
};