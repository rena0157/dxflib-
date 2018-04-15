#pragma once
#include "dxflib++/include/utilities.h"
#include <vector>
#include <string>

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
			lwpolyline,
			hatch,
			all
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

			// Free function
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
				color_name = 430,   // color name
				ignore1 = 1070,     // Ignored do to naming conflict, not used
			};
		}

		/**
		* \brief Entity Base class
		*/
		// ReSharper disable CppPolymorphicClassWithNonVirtualPublicDestructor
		class entity
		{
		public:
			utilities::color color;    // Color of the entity
			// Constructor
			explicit entity(entity_buffer_base&);
			explicit entity();

			// public interface
			const std::string& get_handle() const { return handle_; }             // Returns the entity handle
			const std::string& get_soft_pointer() const { return soft_pointer_; } // Returns the entity soft pointer
			const std::string& get_layer() const { return layer_; }               // Returns the entity layer

		protected:
			std::string layer_;        // Layer the entity is on 
			std::string handle_;       // Handle of the entity
			std::string soft_pointer_; // Soft pointer to another entity's handle
			std::string color_name_;   // ACAD color name
			int raw_color_;            // raw color value

			// geometry
			virtual void recalculate_geometry();
		};
	}
	
}
