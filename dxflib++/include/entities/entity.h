#pragma once
#include <string>

namespace dxflib
{
	/**
	 * \brief Entity Types that are to be parsed
	 */
	enum class entity_types
	{
		line
	};

	/**
	 * \brief Entity Buffer Base struct that is used in the derived buffer classes
	 */
	struct entity_buffer_base
	{
		virtual ~entity_buffer_base();
		std::string layer{};
		std::string handle{};
		std::string soft_pointer{};
		virtual int parse(const std::string& cl, const std::string& nl);
	};

	namespace group_codes
	{
		/**
		* \brief Group Codes common to all entities
		*/
		enum class entity_codes
		{
			error,
			layer = 8,
			handle = 5,
			soft_pointer = 330
		};
	}

	/**
	 * \brief Entity Base class
	 */
	class entity
	{
	public:
		std::string layer;
		std::string handle;
		explicit entity(entity_buffer_base&);
	protected:
		std::string soft_pointer_;
	};
}
