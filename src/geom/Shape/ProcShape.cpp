//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <geom/Generated/Types.h>
#include <geom/Shape/ProcShape.h>
#include <geom/Shape/DrawShape.h>

#include <geom/Shape/Line.h>
#include <geom/Shape/Circle.h>
#include <geom/Shape/Quad.h>
#include <geom/Shape/Triangle.h>

#include <geom/Shape/Cube.h>
#include <geom/Shape/Cylinder.h>
#include <geom/Shape/Sphere.h>
#include <geom/Shape/Spheroid.h>
#include <geom/Shape/Geom.h>

#include <geom/Primitive.h>
#include <geom/Shapes.h>
#include <geom/ShapesComplex.h>
#include <geom/Aabb.h>

namespace mud
{
	using Draw = DispatchDrawProcShape;

	ShapeSize symbol_line_size(const ProcShape& procshape)
	{
		const Shape& shape = *procshape.m_shape;
		if(Draw::me().m_size_lines.check(&shape))
			return Draw::me().m_size_lines.dispatch(&shape, procshape);
		return { 0, 0 };
	}

	ShapeSize symbol_triangle_size(const ProcShape& procshape)
	{
		const Shape& shape = *procshape.m_shape;
		if(Draw::me().m_size_triangles.check(&shape))
			return Draw::me().m_size_triangles.dispatch(&shape, procshape);
		return{ 0, 0 };
	}

	void symbol_draw_lines(const ProcShape& procshape, MeshData& data)
	{
		const Shape& shape = *procshape.m_shape;
		if(Draw::me().m_draw_lines.check(&shape))
			Draw::me().m_draw_lines.dispatch(&shape, procshape, data);
	}

	void symbol_draw_triangles(const ProcShape& procshape, MeshData& data)
	{
		const Shape& shape = *procshape.m_shape;
		if(Draw::me().m_draw_triangles.check(&shape))
			Draw::me().m_draw_triangles.dispatch(&shape, procshape, data);
	}

	ShapeSize size_shape_lines(const ProcShape& procshape, const CompoundShape& compound)
	{
		UNUSED(procshape);
		ShapeSize result = { 0, 0 };
		for(auto& shape : compound.m_shapes)
			result.vec += symbol_line_size(shape).vec;
		return result;
	}

	void draw_shape_lines(const ProcShape& procshape, const CompoundShape& compound, MeshData& data)
	{
		UNUSED(procshape);
		for(auto& shape : compound.m_shapes)
		{
			symbol_draw_lines(shape, data);
			data.next();
		}
	}

	ShapeSize size_shape_triangles(const ProcShape& procshape, const CompoundShape& compound)
	{
		UNUSED(procshape);
		ShapeSize result = { 0, 0 };
		for(auto& shape : compound.m_shapes)
			result.vec += symbol_triangle_size(shape).vec;
		return result;
	}

	void draw_shape_triangles(const ProcShape& procshape, const CompoundShape& compound, MeshData& data)
	{
		UNUSED(procshape);
		for(auto& shape : compound.m_shapes)
		{
			symbol_draw_triangles(shape, data);
			data.next();
		}
	}

	DispatchDrawProcShape::DispatchDrawProcShape()
	{
		declare_shape<Line>(*this);
		declare_shape<Circle>(*this);
		declare_shape<Ellipsis>(*this);
		declare_shape<Grid2>(*this);
		declare_shape<Quad>(*this);
		declare_shape<Rect>(*this);
		declare_shape<Triangle>(*this);

		declare_shape<Box>(*this);
		declare_shape<Cube>(*this);
		declare_shape<Aabb>(*this);
		declare_shape<Cylinder>(*this);
		declare_shape<Sphere>(*this);

		declare_shape<Geometry>(*this);

		declare_compound_shape<Spheroid>(*this);
	}
}
