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

#include "Noise.h"
#include "NoiseUtils.h"

namespace noisepp
{

void Module::write (utils::OutStream &s) const
{
}

void Module::read (utils::InStream &s)
{
}

void PerlinModuleBase::write (utils::OutStream &s) const
{
	s.writeDouble (mFrequency);
	s.writeInt (mOctaveCount);
	s.writeInt (mSeed);
	s.writeInt (mQuality);
	s.writeDouble (mLacunarity);
	s.writeDouble (mPersistence);
	s.writeDouble (mScale);
}

void PerlinModuleBase::read (utils::InStream &s)
{
	mFrequency = static_cast<Real>(s.readDouble ());
	mOctaveCount = s.readInt ();
	mSeed = s.readInt ();
	mQuality = s.readInt ();
    mLacunarity = static_cast<Real>(s.readDouble ());
    mPersistence = static_cast<Real>(s.readDouble ());
    mScale = static_cast<Real>(s.readDouble ());
}

void ClampModule::write (utils::OutStream &s) const
{
	s.writeDouble (mLowerBound);
	s.writeDouble (mUpperBound);
}

void ClampModule::read (utils::InStream &s)
{
    mLowerBound = static_cast<Real>(s.readDouble ());
    mUpperBound = static_cast<Real>(s.readDouble ());
}

void ConstantModule::write (utils::OutStream &s) const
{
	s.writeDouble (mValue);
}

void ConstantModule::read (utils::InStream &s)
{
    mValue = static_cast<Real>(s.readDouble ());
}

void CurveModule::write (utils::OutStream &s) const
{
	int count = (int)mControlPoints.size ();
	s.writeInt (count);
	for (int i=0;i<count;++i)
	{
		s.writeDouble (mControlPoints[i].inValue);
		s.writeDouble (mControlPoints[i].outValue);
	}
}

void CurveModule::read (utils::InStream &s)
{
	mControlPoints.clear ();
	int count = s.readInt ();
	for (int i=0;i<count;++i)
	{
		double inValue = static_cast<Real>(s.readDouble ());
		double outValue = static_cast<Real>(s.readDouble ());
        addControlPoint (static_cast<Real>(inValue), static_cast<Real>(outValue));
	}
}

void ExponentModule::write (utils::OutStream &s) const
{
	s.writeDouble (mExponent);
}

void ExponentModule::read (utils::InStream &s)
{
    mExponent = static_cast<Real>(s.readDouble ());
}

void RidgedMultiModule::write (utils::OutStream &s) const
{
	s.writeDouble (mFrequency);
	s.writeInt (mOctaveCount);
	s.writeInt (mSeed);
	s.writeInt (mQuality);
	s.writeDouble (mLacunarity);
	s.writeDouble (mExponent);
	s.writeDouble (mOffset);
	s.writeDouble (mGain);
	s.writeDouble (mScale);
}

void RidgedMultiModule::read (utils::InStream &s)
{
	mFrequency = static_cast<Real>(s.readDouble ());
	mOctaveCount = s.readInt ();
	mSeed = s.readInt ();
	mQuality = s.readInt ();
    mLacunarity = static_cast<Real>(s.readDouble ());
    mExponent = static_cast<Real>(s.readDouble ());
    mOffset = static_cast<Real>(s.readDouble ());
    mGain = static_cast<Real>(s.readDouble ());
    mScale = static_cast<Real>(s.readDouble ());
}

void ScaleBiasModule::write (utils::OutStream &s) const
{
	s.writeDouble (mScale);
	s.writeDouble (mBias);
}

void ScaleBiasModule::read (utils::InStream &s)
{
	mScale = static_cast<Real>(s.readDouble ());
	mBias = static_cast<Real>(s.readDouble ());
}

void ScalePointModule::write (utils::OutStream &s) const
{
	s.writeDouble (mScaleX);
	s.writeDouble (mScaleY);
	s.writeDouble (mScaleZ);
}

void ScalePointModule::read (utils::InStream &s)
{
	mScaleX = static_cast<Real>(s.readDouble ());
	mScaleY = static_cast<Real>(s.readDouble ());
	mScaleZ = static_cast<Real>(s.readDouble ());
}

void SelectModule::write (utils::OutStream &s) const
{
	s.writeDouble (mLowerBound);
	s.writeDouble (mUpperBound);
	s.writeDouble (mEdgeFalloff);
}

void SelectModule::read (utils::InStream &s)
{
	mLowerBound = static_cast<Real>(s.readDouble ());
	mUpperBound = static_cast<Real>(s.readDouble ());
	mEdgeFalloff = static_cast<Real>(s.readDouble ());
}

void TerraceModule::write (utils::OutStream &s) const
{
	s.writeInt (mInvert);
	int count = (int)mControlPoints.size ();
	s.writeInt (count);
	for (int i=0;i<count;++i)
	{
		s.writeDouble (mControlPoints[i]);
	}
}

void TerraceModule::read (utils::InStream &s)
{
	mControlPoints.clear ();
	mInvert = (s.readInt() != 0);
	int count = s.readInt ();
	for (int i=0;i<count;++i)
	{
        addControlPoint (static_cast<Real>(s.readDouble ()));
	}
}

void TranslatePointModule::write (utils::OutStream &s) const
{
	s.writeDouble (mTranslationX);
	s.writeDouble (mTranslationY);
	s.writeDouble (mTranslationZ);
}

void TranslatePointModule::read (utils::InStream &s)
{
	mTranslationX = static_cast<Real>(s.readDouble ());
	mTranslationY = static_cast<Real>(s.readDouble ());
	mTranslationZ = static_cast<Real>(s.readDouble ());
}

void TurbulenceModule::write (utils::OutStream &s) const
{
	s.writeDouble (mPower);
	s.writeInt (getRoughness());
	s.writeInt (getSeed());
	s.writeDouble (getFrequency());
	s.writeInt (getQuality());
}

void TurbulenceModule::read (utils::InStream &s)
{
	mPower = static_cast<Real>(s.readDouble ());
	setRoughness (s.readInt());
	setSeed (s.readInt());
    setFrequency (static_cast<Real>(s.readDouble ()));
	setQuality (s.readInt());
}

void VoronoiModule::write (utils::OutStream &s) const
{
	s.writeDouble (mFrequency);
	s.writeInt (mSeed);
	s.writeDouble (mDisplacement);
	s.writeInt (mEnableDistance);
}

void VoronoiModule::read (utils::InStream &s)
{
    mFrequency = static_cast<Real>(s.readDouble ());
	mSeed = s.readInt ();
	mDisplacement = static_cast<Real>(s.readDouble ());
	mEnableDistance = (s.readInt() != 0);
}

};
