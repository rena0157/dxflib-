#pragma once
#include "dxflib++/include/entities/point.h"
#include "entity.h"

namespace dxflib::entities
{
	namespace group_codes
	{
		enum class text
		{
			thickness = 39,
			first_align_x = 10, first_align_y = 20, first_align_z = 30,
			text_height = 40,
			string = 1,
			text_rotation = 50,
			x_scale = 41,
			oblique = 51,
			text_style = 7,
			text_generation_flags = 71,
			text_justification = 72,
			second_align_x = 11, second_align_y = 21, second_align_z = 31,
			vertical_adjustment = 73,
		};
	}
	struct text_buffer : entity_buffer_base
	{
		// Properties
		double thickness{};
		double first_align_x{}, first_align_y{}, first_align_z{};
		double text_height{};
		std::string string{};
		double text_rotation{};
		double x_scale{};
		double oblique{};
		std::string text_style{};
		// TODO: Add text generation flags
		// TODO: Add text justification
		double second_align_x{}, second_align_y{}, second_align_z{};
		// TODO: Add vertical adjustment

		/**
		 * \brief Parse function used to extract text data from the DXF file
		 * \param cl Current Line from DXF file
		 * \param nl Next Line from DXF file
		 * \return 0: Failure, 1: Success
		 */
		int parse(const std::string& cl, const std::string& nl) override;
		void free() override; // Free function override
	};

    // ReSharper disable CppPolymorphicClassWithNonVirtualPublicDestructor
	/**
	 * \brief text object 
	 */
	class text : entity
	{
	public:

		// Constructor
		explicit text(text_buffer& tb);

		// Public Interface
		double get_thickness() const { return thickness_; }                  // Returns the thickness
		const vertex& first_alignment() const { return first_alignment_; }   // Returns the first alignment vertex
		const vertex& second_alignment() const { return second_alignment_; } // Returns the second alignment vertex
		double height() const { return text_height_; }                       // Returns the text height
		const std::string& get_string() const { return string_; }            // Returns the text string by const&
		std::string get_string() { return string_; }                         // Returns the text string by copy
		double rotation() const { return rotation_; }                        // Returns the rotation angle
		double x_scale() const { return x_scale_; }                          // Returns the x scale factor
		double oblique() const { return oblique_; }                          // Returns the oblique angle
		const std::string& get_style() const { return text_style_; }         // Returns the text style - Const&
		std::string get_style() { return text_style_; }                      // Returns the text style - Copy

	private:
		double thickness_;
		vertex first_alignment_;
		vertex second_alignment_;
		double text_height_;
		std::string string_;
		double rotation_;
		double x_scale_;
		double oblique_;
		std::string text_style_;
	};
}
