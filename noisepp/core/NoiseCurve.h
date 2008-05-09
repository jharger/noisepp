// Noise++ Library
// Copyright (c) 2008, Urs C. Hanselmann
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright notice,
//      this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above copyright notice,
//      this list of conditions and the following disclaimer in the documentation
//      and/or other materials provided with the distribution.
//    * Neither the name of the Noise++ Library's copyright owner nor the names
//      of its contributors may be used to endorse or promote products derived
//      from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

#ifndef NOISEPP_CURVE_H
#define NOISEPP_CURVE_H

#include "NoisePipeline.h"
#include "NoiseModule.h"

namespace noisepp
{
	/// Curve control point.
	struct CurveControlPoint
	{
		/// Input value.
		Real inValue;
		/// Output value.
		Real outValue;
		/// Compare operator for sorting.
		bool operator< (const CurveControlPoint &p) const
		{
			return inValue < p.inValue;
		}
	};

	typedef std::vector<CurveControlPoint> CurveControlPointVector;

	/// Curve module base class.
	template <class Pipeline, class Element>
	class CurveModuleBase : public Module<Pipeline>
	{
		private:
			CurveControlPointVector mControlPoints;

		public:
			/// Constructor.
			CurveModuleBase() : Module<Pipeline>(1)
			{
			}
			/// Adds a control point.
			void addControlPoint (Real inValue, Real outValue)
			{
				CurveControlPoint point;
				point.inValue = inValue;
				point.outValue = outValue;
				mControlPoints.push_back (point);
				std::sort (mControlPoints.begin(), mControlPoints.end());
			}
			/// Clears all control points.
			void clearControlPoints ()
			{
				mControlPoints.clear ();
			}
			/// Returns a reference to the control point vector.
			CurveControlPointVector &getControlPoints ()
			{
				return mControlPoints;
			}
			/// @copydoc noisepp::Module::addToPipeline()
			ElementID addToPipeline (Pipeline *pipe) const
			{
				assert (Module<Pipeline>::getSourceModule (0));
				ElementID first = Module<Pipeline>::getSourceModule(0)->addToPipeline(pipe);
				int count = mControlPoints.size ();
				assert (count >= 4);
				CurveControlPoint *points = new CurveControlPoint[count];
				for (int i=0;i<count;++i)
				{
					points[i] = mControlPoints[i];
				}
				return pipe->addElement (this, new Element(pipe, first, points, count));
			}
	};

	template <class PipelineElement>
	class CurveElementBase : public PipelineElement
	{
		protected:
			ElementID mElement;
			const PipelineElement *mElementPtr;
			CurveControlPoint *mControlPoints;
			int mControlPointCount;

			NOISEPP_INLINE int clampValue (int i, int lo, int hi) const
			{
				if (i < lo)
					return lo;
				else if (i > hi)
					return hi;
				else
					return i;
			}

			NOISEPP_INLINE Real mapValue (Real value) const
			{
				int index;
				for (index=0;index<mControlPointCount;++index)
				{
					if (value < mControlPoints[index].inValue)
					{
						break;
					}
				}

				const int index0 = clampValue (index-2, 0, mControlPointCount-1);
				const int index1 = clampValue (index-1, 0, mControlPointCount-1);
				const int index2 = clampValue (index, 0, mControlPointCount-1);
				const int index3 = clampValue (index+1, 0, mControlPointCount-1);

				if (index1 == index2)
				{
					return mControlPoints[index1].outValue;
				}

				const Real in0 = mControlPoints[index1].inValue;
				const Real in1 = mControlPoints[index2].inValue;
				const Real a = (value - in0) / (in1 - in0);
				return Math::InterpCubic (mControlPoints[index0].outValue, mControlPoints[index1].outValue, mControlPoints[index2].outValue, mControlPoints[index3].outValue, a);
			}
		public:
			CurveElementBase (const Pipeline<PipelineElement> *pipe, ElementID element, CurveControlPoint *points, int count) : mElement(element), mControlPoints(points), mControlPointCount(count)
			{
				assert (points);
				assert (count >= 4);
				mElementPtr = pipe->getElement (mElement);
			}
			virtual ~CurveElementBase ()
			{
				delete[] mControlPoints;
				mControlPoints = NULL;
			}
	};

	class CurveElement1D : public CurveElementBase<PipelineElement1D>
	{
		public:
			CurveElement1D (const Pipeline1D *pipe, ElementID element, CurveControlPoint *points, int count) : CurveElementBase<PipelineElement1D>(pipe, element, points, count)
			{
			}
			virtual Real getValue (Real x, Cache *cache) const
			{
				Real value;
				value = getElementValue (mElementPtr, mElement, x, cache);
				return CurveElementBase<PipelineElement1D>::mapValue(value);
			}
	};

	class CurveElement2D : public CurveElementBase<PipelineElement2D>
	{
		public:
			CurveElement2D (const Pipeline2D *pipe, ElementID element, CurveControlPoint *points, int count) : CurveElementBase<PipelineElement2D>(pipe, element, points, count)
			{
			}
			virtual Real getValue (Real x, Real y, Cache *cache) const
			{
				Real value;
				value = getElementValue (mElementPtr, mElement, x, y, cache);
				return CurveElementBase<PipelineElement2D>::mapValue(value);
			}
	};

	class CurveElement3D : public CurveElementBase<PipelineElement3D>
	{
		public:
			CurveElement3D (const Pipeline3D *pipe, ElementID element, CurveControlPoint *points, int count) : CurveElementBase<PipelineElement3D>(pipe, element, points, count)
			{
			}
			virtual Real getValue (Real x, Real y, Real z, Cache *cache) const
			{
				Real value;
				value = getElementValue (mElementPtr, mElement, x, y, z, cache);
				return CurveElementBase<PipelineElement3D>::mapValue(value);
			}
	};

	/** 1D module that maps the values from the source module onto a curve.
		Maps the values from the source modules onto the curve defined by the specified control points (at least 4)
	*/
	class CurveModule1D : public CurveModuleBase<Pipeline1D, CurveElement1D>
	{ };
	/** 2D module that maps the values from the source module onto a curve.
		Maps the values from the source modules onto the curve defined by the specified control points (at least 4)
	*/
	class CurveModule2D : public CurveModuleBase<Pipeline2D, CurveElement2D>
	{ };
	/** 3D module that maps the values from the source module onto a curve.
		Maps the values from the source modules onto the curve defined by the specified control points (at least 4)
	*/
	class CurveModule3D : public CurveModuleBase<Pipeline3D, CurveElement3D>
	{ };
};

#endif
