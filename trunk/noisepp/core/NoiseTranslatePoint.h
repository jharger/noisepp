#ifndef NOISEPP_TRANSLATEPOINT_H
#define NOISEPP_TRANSLATEPOINT_H

namespace noisepp
{
	class TranslatePointElement1D : public PipelineElement1D
	{
		private:
			ElementID mElement;
			const PipelineElement1D *mElementPtr;
			Real mTranslationX;

		public:
			TranslatePointElement1D (const Pipeline1D *pipe, ElementID element, Real TranslationX) :
				mElement(element), mTranslationX(TranslationX)
			{
				mElementPtr = pipe->getElement (mElement);
			}
			virtual Real getValue (Real x, Cache *cache) const
			{
				return getElementValue (mElementPtr, mElement, x+mTranslationX, cache);
			}

	};

	/** 1D transform module for translating.
		Transforms the source module by translating the coordinates.
	*/
	class TranslatePointModule1D : public Module1D
	{
		private:
			Real mTranslationX;

		public:
			/// Constructor.
			TranslatePointModule1D() : Module1D(1), mTranslationX(0.0)
			{
			}
			/// Sets the translation applied to the x coordintate.
			void setTranslationX (Real v)
			{
				mTranslationX = v;
			}
			/// Returns the translation applied to the x coordintate.
			Real getTranslationX () const
			{
				return mTranslationX;
			}
			/// @copydoc noisepp::Module::addToPipeline()
			virtual ElementID addToPipeline (Pipeline1D *pipe) const
			{
				assert (getSourceModule (0));
				ElementID first = getSourceModule(0)->addToPipeline(pipe);
				return pipe->addElement (this, new TranslatePointElement1D(pipe, first, mTranslationX));
			}
	};

	class TranslatePointElement2D : public PipelineElement2D
	{
		private:
			ElementID mElement;
			const PipelineElement2D *mElementPtr;
			Real mTranslationX;
			Real mTranslationY;

		public:
			TranslatePointElement2D (const Pipeline2D *pipe, ElementID element, Real TranslationX, Real TranslationY) :
				mElement(element), mTranslationX(TranslationX), mTranslationY(TranslationY)
			{
				mElementPtr = pipe->getElement (mElement);
			}
			virtual Real getValue (Real x, Real y, Cache *cache) const
			{
				return getElementValue (mElementPtr, mElement, x+mTranslationX, y+mTranslationY, cache);
			}

	};

	/** 2D transform module for translating.
		Transforms the source module by translating the coordinates.
	*/
	class TranslatePointModule2D : public Module2D
	{
		private:
			Real mTranslationX;
			Real mTranslationY;

		public:
			/// Constructor.
			TranslatePointModule2D() : Module2D(1), mTranslationX(0.0), mTranslationY(0.0)
			{
			}
			/// Sets the translation applied to the x coordintate.
			void setTranslationX (Real v)
			{
				mTranslationX = v;
			}
			/// Returns the translation applied to the x coordintate.
			Real getTranslationX () const
			{
				return mTranslationX;
			}
			/// Sets the translation applied to the y coordintate.
			void setTranslationY (Real v)
			{
				mTranslationY = v;
			}
			/// Returns the translation applied to the y coordintate.
			Real getTranslationY () const
			{
				return mTranslationY;
			}
			/// @copydoc noisepp::Module::addToPipeline()
			virtual ElementID addToPipeline (Pipeline2D *pipe) const
			{
				assert (getSourceModule (0));
				ElementID first = getSourceModule(0)->addToPipeline(pipe);
				return pipe->addElement (this, new TranslatePointElement2D(pipe, first, mTranslationX, mTranslationY));
			}
	};

	class TranslatePointElement3D : public PipelineElement3D
	{
		private:
			ElementID mElement;
			const PipelineElement3D *mElementPtr;
			Real mTranslationX;
			Real mTranslationY;
			Real mTranslationZ;

		public:
			TranslatePointElement3D (const Pipeline3D *pipe, ElementID element, Real TranslationX, Real TranslationY, Real TranslationZ) :
				mElement(element), mTranslationX(TranslationX), mTranslationY(TranslationY), mTranslationZ(TranslationZ)
			{
				mElementPtr = pipe->getElement (mElement);
			}
			virtual Real getValue (Real x, Real y, Real z, Cache *cache) const
			{
				return getElementValue (mElementPtr, mElement, x+mTranslationX, y+mTranslationY, z+mTranslationZ, cache);
			}

	};

	/** 3D transform module for translating.
		Transforms the source module by translating the coordinates.
	*/
	class TranslatePointModule3D : public Module3D
	{
		private:
			Real mTranslationX;
			Real mTranslationY;
			Real mTranslationZ;

		public:
			/// Constructor.
			TranslatePointModule3D() : Module3D(1), mTranslationX(0.0), mTranslationY(0.0), mTranslationZ(0.0)
			{
			}
			/// Sets the translation applied to the x coordintate.
			void setTranslationX (Real v)
			{
				mTranslationX = v;
			}
			/// Returns the translation applied to the x coordintate.
			Real getTranslationX () const
			{
				return mTranslationX;
			}
			/// Sets the translation applied to the y coordintate.
			void setTranslationY (Real v)
			{
				mTranslationY = v;
			}
			/// Returns the translation applied to the y coordintate.
			Real getTranslationY () const
			{
				return mTranslationY;
			}
			/// Sets the translation applied to the z coordintate.
			void setTranslationZ (Real v)
			{
				mTranslationZ = v;
			}
			/// Returns the translation applied to the z coordintate.
			Real getTranslationZ () const
			{
				return mTranslationZ;
			}
			/// @copydoc noisepp::Module::addToPipeline()
			virtual ElementID addToPipeline (Pipeline3D *pipe) const
			{
				assert (getSourceModule (0));
				ElementID first = getSourceModule(0)->addToPipeline(pipe);
				return pipe->addElement (this, new TranslatePointElement3D(pipe, first, mTranslationX, mTranslationY, mTranslationZ));
			}
	};
};

#endif // NOISEPP_TRANSLATEPOINT_H
