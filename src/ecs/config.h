#ifndef TBGE_SRC_ECS_CONFIG_H_
#define TBGE_SRC_ECS_CONFIG_H_

#include <cstdint>

// Set these defines if the datatype used for entities or component types is too
// small. They both default to 16 bit unsigned integers, giving 65536 of each.
// While it is unlikely that you will have more than 65536 different component
// types, having more Entities than that is completely feasible. At which point
// increasing the datatype will be necessary, but note that if you do that the
// maximum definition should also be raised.

// #define ECS_ENTITY_DATATYPE std::uint16_t
// #define ECS_COMPONENT_TYPE_DATATYPE std::uint16_t

// Set these defines to define a maximum amount of entities and components, this
// is to protect against heap overflow.

#define ECS_MAX_ENTITIES 50000
#define ECS_MAX_COMPONENT_TYPES 5000

#endif