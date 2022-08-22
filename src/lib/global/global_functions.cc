// NOLINT(legal/copyright)
/*
* _____________________________
*    _____ ____   ____ _____   
*   |_   _| __ ) / ___| ____|  
*     | | |  _ \| |  _|  _|    
*     | | | |_) | |_| | |___   
*     |_| |____/ \____|_____|  
* _____________________________
*/

#include "src/lib/global/global_functions.hh"

#include <string>
#include <iostream>

namespace tbge {
namespace global {

/// @todo make a proper markup parser
void parse_print(std::string s) {
  std::cout << s;
}

}  // namespace global
}  // namespace tbge

