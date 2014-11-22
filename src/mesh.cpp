
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/multi/geometries/multi_point.hpp>

#include <iostream>
#include <vector>

#include "mesh.h"
#include "component.h"
#include "vertex.h"

void Mesh::createHull(int c_num)
{


	using boost::geometry::append;
	using boost::geometry::make;
	using boost::geometry::model::d2::point_xy;

	boost::geometry::model::multi_point<point_xy<dReal> > pointset;

	for (int i = 0; i < components.at(c_num)->faces.size(); i++)
	{
		for (std::vector<int>::iterator vertIter = components.at(c_num)->faces.at(i)->vertices.begin(); vertIter != components.at(c_num)->faces.at(i)->vertices.end(); vertIter++)
		{
			append(pointset, make<point_xy<dReal> >(vertexPalette.at(*vertIter)->pos.x, vertexPalette.at(*vertIter)->pos.y));
		}
	}

	boost::geometry::model::multi_point<point_xy<dReal> > hull;
	boost::geometry::convex_hull(pointset, hull);

	for (std::vector<point_xy<dReal> >::size_type i = 0; i < hull.size(); i++)
	{
		components.at(c_num)->hull.push_back(std::make_pair(boost::geometry::get<0>(hull[i]), boost::geometry::get<1>(hull[i])));
	}


}
