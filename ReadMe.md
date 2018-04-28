## DxfLib++ - An AutoCAD DXF Library

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

#### Entities
- [Entity](#Entity): Entity Base Class
- [Vertex](#Vertex): Cartesian coordinate vector 
- [LINE](#LINE): AutoCAD LINE Entity
- [Geoline](#Geoline): Geometric Line
- LWPOLYLINE: 
- HATCH
- TEXT
- MTEXT


## Entities

### Entity <a name="entity"></a>

The [`dxflib::entities::entity`](#entity) base class is the parent class for all entities in the library. Properties and
methods:

#### Constructors<a name="entity::constructors"></a>

- `explicit entity(entity_buffer_base&);`: default dxf constructor.
  - This constructer uses the `entity_buffer_base` class which is created in the parsing function during dxf \
  extraction. The use of this constructor out of this scope is proably not very common.
- `explicit entity();`: Default Constructor.

#### Public Methods<a name="entity::public_methods"></a>

- `const std::string& get_handle() const`: returns the entity [`handle_`](#entity::protected_members) 
- `const std::string& get_soft_pointer() const`: returns the entity [`soft_pointer_`](#entity::protected_members) 
- `const std::string& get_layer() const;`: returns the entity [`layer_`](#entity::protected_members) 
- `const utilities::color& get_color() const;` returns the entity [`color_`](#entity::protected_members) 

#### Protected Members<a name="entity::protected_members"></a>

- `std::string layer_;`: The layer that the entity or derived class is on in the dxf file.
- `std::string handle;`: The handle of the entity.
- `std::string soft_pointer_;`: The soft pointer (Handle of another entity) of the entity.
- `std::color_name_;` **NOT IMPLEMENTED**
- `int raw_color_;`: raw color of the entity. Extracted from a 24-bit hex color code
- `utilities::color color_`: Color of the entity. The custom color class is used here.

### Vertex
**Derived Class**\
Vertex ---> [point_base](#point_base)

#### point_base
The point base class is the parent class for the vertex. There are really not that many
differences between the two at this point. That said I felt that the point_base did not
warrent its own subsection.

#### Constructors
- `explicit vertex(double x = 0, double y = 0, double z = 0);`: Default and only
Constructor for the vertex class.

#### Public Members
- `double x, y, z;`: Cartesian Coordinates for the vertex
- `friend std::ostream& operator<<;`: Operator overload for printing.

### LINE

**Derived Class**\
`class line : public` [`entity`](#entity);

LINE is the DxfLib++ library implementation of the LINE entity in AutoCAD DXF. 
The line entity is a 3D line that is defined by two points.

#### Constructors
- `explicit line(line_buf&)`: Default dxf line constructor

#### Public Members
- `const vertex& get_vertex(int id) const;`: returns [`vertex`](#vertex) by id
- `void move_vertex(int id, const vertex& new_vertex);`: moves the `vertex`(`id`) to\
a new position(`new_vertex`). The Line will then update the `length_`.
- `double get_thickness() const;`: returns the thickness of the line
- `lwpolyline to_lwpolyline() const;` converts the line into a `lwpolyline` and then \
returns a copy of that `lwpolyline`. Note: Depending on the implementation and optimization\
The new `lwpolyline` might be moved to the new location.

#### Private Members
- `vertex v0_;`: The starting [`vertex`](#vertex) of the line.
- `vertex v1_;`: The ending `vertex` of the line.
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

Geoline = **Geo**metric **line**. The geometric line is more or less the same as the 
[LINE](#LINE) class. The only difference is that the geoline is not a derived class of 
the [Entity](#entity) class. This makes the geoline class more compact and usefull for
geometric calculations. A geoline can also be polymorphic in the sense that it can either
be an arc or a line.


#### Static Members
- `static constexpr int bulge_null{-2};` value used to determine wether a geoline 
is an arc or a line. if the bulge of a geoline is `geoline::bulge_null;` then the geoline
is a straight line.
- `static std::vector<geoline> geoline_binder(const std::vector<double>& x,
		                                           const std::vector<double>& y, const std::vector<double>& bulge,
		                                           bool is_closed);`:
Function that takes three vectors, an x vector, a y vector and a bulge vector. The 
Funciton then "binds" the vectors into points and then into geolines. The return is a 
geoline vector.
	- Will throw an `std::invalid_argument` exception if the input vectors are not the
    same length.

#### Constructors
- `explicit geoline(const vertex& v0, const vertex& v1, double bulge = bulge_null);`
the default constructor. Takes in two `vertex` objects and a default parameter 

#### Public Members
- `const vertex& operator[](int id) const;`: Returns a vertex by its id.
	- `vertex& operator[](int id);` Overload of above with a non const reference.
- `inline double get_length() const;`: Returns the total length of the geoline.
- `double get_bulge() const;`Returns the bulge of the geoline
- `double get_area() const;`: Returns the area between the geoline and the x-axis
- `inline double get_radius() const;`: Returns the radius of the geoline. Will return
`INF` if `bulge_== bulge_null`. 
- `inline double get_angle() const;`: Returns the total angle between the two legs of the
arc. Will return `INF` if `bulge_ == bulge_null`.
- `std::ostream& operator<<;`: Overload operator for printing geolines.

#### Protected Members
- `vertex v0_;`: Starting [`vertex`](#vertex) of the geoline
- `vertex v1_;`: Ending [`vertex`](#vertex) of the geoline
- `double bulge_;`: Bulge of the geoline
- `double length_;`: Total length of the geoline
- `double radius_;`: Radius of the geoline if it is an arc segment
- `double total_angle_;`: Total angle of the geoline if it is an arc.
- `double area_;`: Total area between the geoline and the x-axis