#include "dxflib++/include/entities/text.h"

int dxflib::entities::text_buffer::parse(const std::string& cl, const std::string& nl)
{

	int code{ entity_buffer_base::parse(cl, nl) };
	// Convert the current line to an int with this try block
	if (code == -1)
	{
		return 1;
	}
	// Parse Tree
	switch(static_cast<entities::group_codes::text>(code))
	{
	case group_codes::text::first_align_x:
		first_align_x = std::stod(nl);
		return 1;
	case group_codes::text::first_align_y:
		first_align_y = std::stod(nl);
		return 1;
	case group_codes::text::first_align_z:
		first_align_z = std::stod(nl);
		return 1;
	case group_codes::text::text_height:
		text_height = std::stod(nl);
		return 1;
	case group_codes::text::string:
		string = nl;
		return 1;
	case group_codes::text::text_rotation:
		text_rotation = std::stod(nl);
		return 1;
	case group_codes::text::x_scale:
		x_scale = std::stod(nl);
		return 1;
	case group_codes::text::oblique:
		oblique = std::stod(nl);
		return 1;
	case group_codes::text::text_style:
		text_style = nl;
		return 1;
	case group_codes::text::text_generation_flags:
		return 1;
	case group_codes::text::text_justification:
		return 1;
	case group_codes::text::second_align_x:
		second_align_x = std::stod(nl);
		return 1;
	case group_codes::text::second_align_y:
		second_align_y = std::stod(nl);
		return 1;
	case group_codes::text::second_align_z:
		second_align_z = std::stod(nl);
		return 1;
	case group_codes::text::vertical_adjustment:
		return 1;
	default: return 0;
	}

}

void dxflib::entities::text_buffer::free()
{
	thickness = 0;
	first_align_x = 0; first_align_x = 0; first_align_z = 0;
	text_height = 0; string = ""; string.shrink_to_fit();
	text_rotation = 0;
	x_scale = 0;
	oblique = 0;
	text_style = ""; text_style.shrink_to_fit();
	second_align_x = 0; second_align_y = 0; second_align_z = 0;
}

dxflib::entities::text::text(text_buffer& tb) :
	entity(tb), thickness_(tb.thickness),
	first_alignment_(tb.first_align_x, tb.first_align_y, tb.first_align_z),
	second_alignment_(tb.second_align_x, tb.second_align_y, tb.second_align_z),
	text_height_(tb.text_height), string_(std::move(tb.string)),
	rotation_(tb.text_rotation), x_scale_(tb.x_scale), oblique_(tb.oblique),
	text_style_(std::move(tb.text_style))
{

}
