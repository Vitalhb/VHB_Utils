#pragma once

template <typename T, const uint8_t SampleSize> class TSampler
{
public:
	TSampler(T ldiffThreshold)  __attribute__((always_inline)) 
	{
		diffThreshold = ldiffThreshold;
		sampleCounter = 0;
		for (uint8_t i = 0; i < SampleSize; i++)
			samples[i] = 0;
	}

	// Store new sample
	void storeSample(T sample) __attribute__((always_inline))
	{
		if (sampleCounter < SampleSize)
			samples[sampleCounter++] = sample;
	}

	uint8_t GetSamplesNumber() __attribute__((always_inline))
	{
		return sampleCounter;
	}

	void startSampling() __attribute__((always_inline))
	{
		sampleCounter = 0;
	}

	// eliminate the worst sample and calculate the average
	T sampleAverage();
private:
	T samples[SampleSize];
	T diffThreshold;
	uint8_t sampleCounter;
};

template <typename T, const uint8_t SampleSize>
T TSampler<T, SampleSize>::sampleAverage()
{
	T average = 0, maxDiff = 0;
	uint8_t i, worst = 0;

	for (i = 0; i < sampleCounter; i++)
		average += samples[i];

	average /= sampleCounter;

	// Find the worst sample
	for (i = 0; i < sampleCounter; i++)
	{
		T diff = abs(samples[i] - average);
		if (diff > maxDiff)
		{
			worst = i;
			maxDiff = diff;
		}
	}

	if (diffThreshold > 0 && maxDiff > diffThreshold)
	{
		average = 0;

		// Recalculate average eliminating the worst sample
		for (i = 0; i < sampleCounter; i++)
		{
			if (i != worst)
				average += samples[i];
		}
		average /= sampleCounter - 1;
	}

	return average;
}
