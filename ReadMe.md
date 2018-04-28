## DxfLib++

````
dxflib::cadfile c_file{"Path.dxf"}; // Load file

// Iterate through all of the hatches in the file and print
// the handle of the hatch, its perimeter and its area:
for (const auto& hatch : c_file.get_hatches())
{
	std::cout << "Hatch: " << hatch.get_handle()
			  << "perimeter: " << hatch.get_perimeter() <<
              << "area: " << hatch.get_area() << "\n";
}	
````

DxfLib++ is a library that parses and extracts data from AutoCAD dxf files and builds them into
C++ classes.

#### AutoCAD Entities Currently Supported

- LINE
- LWPOLYLINE
- HATCH
- TEXT
- MTEXT


## Entities

### Entity <a name="entity"></a>

The [`dxflib::entities::entity`](#entity) base class is the parent class for all entities in the library. Properties and
methods:

#### Members and Methods

##### `Constructors` <a name="entity::constructors"></a>

- `explicit entity(entity_buffer_base&);`: default dxf constructor.
  - This constructer uses the `entity_buffer_base` class which is created in the parsing function during dxf \
  extraction. The use of this constructor out of this scope is proably not very common.
- `explicit entity();`: Default Constructor.

##### `Public Methods` <a name="entity::public_methods"></a>

- `const std::string& get_handle() const`: returns the entity [`handle_`](#entity::protected_members) 
- `const std::string& get_soft_pointer() const`: returns the entity [`soft_pointer_`](#entity::protected_members) 
- `const std::string& get_layer() const;`: returns the entity [`layer_`](#entity::protected_members) 
- `const utilities::color& get_color() const;` returns the entity [`color_`](#entity::protected_members) 

##### `Protected Members` <a name="entity::protected_members"></a>

- `std::string layer_;`: The layer that the entity or derived class is on in the dxf file.
- `std::string handle;`: The handle of the entity.
- `std::string soft_pointer_;`: The soft pointer (Handle of another entity) of the entity.
- `std::color_name_;` **NOT IMPLEMENTED**
- `int raw_color_;`: raw color of the entity. Extracted from a 24-bit hex color code
- `utilities::color color_`: Color of the entity. The custom color class is used here.

### LINE

**Derived Class**\
`class line : public` [`entity`](#entity);

LINE is the DxfLib++ library implementation of the LINE entity in AutoCAD DXF. 
The line entity is a 3D line that is defined by two points.

#### Members and Methods

##### `Constructors` 
- `explicit line(line_buf&)`: Default dxf line constructor

##### `Public Members`
- `const vertex& get_vertex(int id) const;`: returns
- `void move_vertex(int id, const vertex& new_vertex);`: moves the vertex(`id`) to\
a new position(`new_vertex`). The Line will then update the `length_`.
- `double get_thickness() const;`: returns the thickness of the line
- `lwpolyline to_lwpolyline() const;` converts the line into a `lwpolyline` and then \
returns a copy of that `lwpolyline`. Note: Depending on the implementation and optimization\
The new `lwpolyline` might be moved to the new location.

##### `Private Members`
- `vertex v0_;`: The starting vertex of the line.
- `vertex v1_;`: The ending vertex of the line.
- `double thickness_;` The thickness of the line.
- `double length_;`: The total length of the line from `v0_` to `v1_`

#### Example:
```
#include "dxflib++/cadfile.h"

int main()
{
	// Create the cadfile
	dxflib::cadfile c_file{"Path to DXF file"};
	
	// extract a line from the cadfile
	dxflib::entities::line line {c_file.get_lines()[0]};
}
```
### Geoline


