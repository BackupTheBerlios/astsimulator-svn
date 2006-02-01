/***************************************************************************
 *            graph.h
 *
 *  Sun Nov  6 20:51:32 2005
 *  Copyright  2005  Johannes Reinhardt & Florian Brucker
 *	johannes.reinhardt@uni-konstanz.de florian.brucker@uni-konstanz.de
 ****************************************************************************/

/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

template<class NODE, class EDGE> public class Graph {
	private:
	public:
		/**
			Inserts the given edge into the graph.
			
			\param	edge	edge to add
			\param	start	id of start node
			\param	end		id of end node
	
			\returns the new id of the edge
		*/
		int insert_edge(EDGE* edge, int start, int end);
	protected:
};
