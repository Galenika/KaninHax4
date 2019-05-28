#pragma once
class client_entity_list_t
{
public:
	void* get_client_entity(int entity_number)
	{
		return call_virtual_function<void*, 3>(this, entity_number);
	}

	void* get_client_entity_from_handle(unsigned int entity_handle)
	{
		return call_virtual_function<void*, 4>(this, entity_handle);
	}

	int	get_highest_entity_index()
	{
		return call_virtual_function<int, 6>(this);
	}
};