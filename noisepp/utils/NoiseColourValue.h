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

#ifndef NOISECOLOURVALUE_H
#define NOISECOLOURVALUE_H

namespace noisepp
{
namespace utils
{

class ColourValue
{
	public:
		explicit ColourValue(float r=0.0f, float g=0.0f, float b=0.0f);

		void writeRGB (unsigned char *& buffer);

		float r, g, b;

		static unsigned char toUChar (float f);

		inline ColourValue operator+ (const ColourValue& c) const
		{
			ColourValue result;
			result.r = r + c.r;
			result.g = g + c.g;
			result.b = b + c.b;
			return result;
		}
		inline ColourValue operator- (const ColourValue& c) const
		{
			ColourValue result;
			result.r = r - c.r;
			result.g = g - c.g;
			result.b = b - c.b;
			return result;
		}
		inline ColourValue operator* (const ColourValue& c) const
		{
			ColourValue result;
			result.r = r * c.r;
			result.g = g * c.g;
			result.b = b * c.b;
			return result;
		}
		inline ColourValue operator/ (const ColourValue& c) const
		{
			ColourValue result;
			result.r = r / c.r;
			result.g = g / c.g;
			result.b = b / c.b;
			return result;
		}
		inline ColourValue operator* (float f) const
		{
			ColourValue result;
			result.r = r * f;
			result.g = g * f;
			result.b = b * f;
			return result;
		}
		inline ColourValue operator/ (float f) const
		{
			ColourValue result;
			result.r = r / f;
			result.g = g / f;
			result.b = b / f;
			return result;
		}
		inline ColourValue &operator += (const ColourValue& c)
		{
			r += c.r;
			g += c.g;
			b += c.b;
			return *this;
		}
		inline ColourValue &operator -= (const ColourValue& c)
		{
			r -= c.r;
			g -= c.g;
			b -= c.b;
			return *this;
		}
		inline ColourValue &operator *= (const ColourValue& c)
		{
			r *= c.r;
			g *= c.g;
			b *= c.b;
			return *this;
		}
		inline ColourValue &operator /= (const ColourValue& c)
		{
			r /= c.r;
			g /= c.g;
			b /= c.b;
			return *this;
		}
		inline ColourValue &operator *= (float f)
		{
			r *= f;
			g *= f;
			b *= f;
			return *this;
		}
		inline ColourValue &operator /= (float f)
		{
			r /= f;
			g /= f;
			b /= f;
			return *this;
		}

	protected:
	private:
};

};
};

#endif // NOISECOLOURVALUE_H