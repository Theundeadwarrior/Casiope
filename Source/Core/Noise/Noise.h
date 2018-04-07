#pragma once

namespace Core
{
	enum NoiseQuality
	{
		NoiseQuality_Fast,
		NoiseQuality_Normal,
		NoiseQuality_Best
	};

	class PerlinNoise
	{
	public:
		PerlinNoise();
		~PerlinNoise();

		double GetValue(double x, double y, double z) const;

		double m_Frequency;
		double m_Lacunarity;
		double m_Persistence;
		NoiseQuality m_NoiseQuality;
		int m_OctaveCount;
		int m_Seed;

	};

	double SCurve3(double a);
	double SCurve5(double a);
	double LinearInterp(double n0, double n1, double a);

	double MakeInt32Range(double n);

	double GradientCoherentNoise3D(double x, double y, double z, int seed, NoiseQuality noiseQuality);
	double GradientNoise3D(double fx, double fy, double fz, int ix, int iy, int iz, int seed);
}
