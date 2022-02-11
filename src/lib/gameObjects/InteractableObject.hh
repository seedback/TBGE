/*
* _____________________________
*    _____ ____   ____ _____   
*   |_   _| __ ) / ___| ____|  
*     | | |  _ \| |  _|  _|    
*     | | | |_) | |_| | |___   
*     |_| |____/ \____|_____|  
* _____________________________
*/

/*
	Class definition for the basic interactable object class.
	This class is used for all objects that will react to one or more
		dynamically generated commands consisting of a command-word and one or
		more descriptors.
	Is not meant to be used by itself, but to be inherited from. Though items
		that can be interacted with but with no other pre-defined behaviour other
		than a description, this can be used.
	OBS: Objects of this class cannot be added to an inventory.
		For that see the ObtainableItems class
*/


#include <string>
#include <vector>

//#include "lib/command/Command.hh"

class InteractableObjects {
	public:

	private:
		std::string name = "";
		//std::vector<Command> commands;
};