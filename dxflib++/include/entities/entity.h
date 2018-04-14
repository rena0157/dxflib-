#pragma once
#include <string>
#include "dxflib++/include/utilities.h"

namespace dxflib
{
	namespace entities
	{
		/**
		* \brief Entity Types that are to be parsed
		*/
		enum class entity_types
		{
			line,
			lwpolyline
		};

		/**
		* \brief Entity Buffer Base struct that is used in the derived buffer classes
		*/
		struct entity_buffer_base
		{
			virtual ~entity_buffer_base();

			// Entity Properties
			std::string layer{};
			std::string handle{};
			std::string soft_pointer{};
			std::string color_name{};
			int raw_color{};

			/**
			* \brief virtual parse function for the entity type: parses data from the dxf file
			* \param cl Current Line
			* \param nl Next Line
			* \return Status -> 0:fail, 1:success
			*/
			virtual int parse(const std::string& cl, const std::string& nl);
			virtual void free();
		};

		namespace group_codes
		{
			/**
			* \brief Group Codes common to all entities
			*/
			enum class entity_codes
			{
				error,
				layer = 8,          // layer that the entity is on
				handle = 5,         // Handle of an entity
				soft_pointer = 330, // Soft pointer to another entity
				raw_color = 420,    // Raw color value: 24 bit (bbggrr) where bb, gg, rr are 8bit integars.
				color_name = 430    // color name
			};
		}

		/**
		* \brief Entity Base class
		*/
		class entity
		{
		public:
			std::string layer;  // Layer the entity is on 
			std::string handle; // Handle of the entity
			utilities::color color;

			// Constructor
			explicit entity(entity_buffer_base&);

		protected:
			
			std::string soft_pointer_; // Soft pointer to another entity's handle
			std::string color_name_;   // ACAD color name
			int raw_color_;            // raw color value
		};
	}
	
}
