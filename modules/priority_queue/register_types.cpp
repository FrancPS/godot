#include "register_types.h"

#include "core/object/class_db.h"
#include "priority_queue.h"

void initialize_priority_queue_module(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		return;
	}
	ClassDB::register_class<PriorityQueue>();
}

void uninitialize_priority_queue_module(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		return;
	}
   // Nothing to do here in this example.
}
