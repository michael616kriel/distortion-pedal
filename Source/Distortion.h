/*
  ==============================================================================

    Distortion.h
    Created: 24 Jul 2021 3:03:15pm
    Author:  Mike

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

template <typename Type>
class Distortion
{

public:

    //==============================================================================
    Distortion()
    {
      
    }

    //==============================================================================
    void prepare(const juce::dsp::ProcessSpec& spec)
    {
        sampleRate = spec.sampleRate;

        auto& waveshaper = processorChain.template get<waveshaperIndex>();
        std::function<Type(Type)> shaperFunc = [&](float x) {
        //     float wetSignal = ((3 * x) / 2) * (1 - (pow(x, 2) / 3));
        //     float wetSignal2 = wetSignal;

        //     wetSignal *= drive * range;
        //     wetSignal2 *= drive * range;

        //     /*
        //     if (wetSignal2 > 0) {
        //         wetSignal2 = 1 - exp(-wetSignal2);
        //     } else {
        //         wetSignal2 = -1 + exp(wetSignal2);
        //     }
        //   */
        //     if (1 < wetSignal && wetSignal < -0.08905f) {
        //         wetSignal = (3 / 4) * (1 - pow(1 - (abs(wetSignal) - 0.032847f), 12) + (1 / 3) * (abs(wetSignal) - 0.032847));
        //     }

        //     if (-0.08905f < wetSignal && wetSignal < 0.320018) {
        //         wetSignal = (-6.153 * pow(wetSignal, 2)) + 3.9375 * wetSignal;
        //     }

        //     if (0.320018 < wetSignal && wetSignal < 1) {
        //         wetSignal = 0.630035;
        //     }

        //     wetSignal = ((wetSignal * blend) + (juce::jlimit(Type(-1), Type(1), wetSignal2) * (1.0f / blend) / 2)) * volume;

        //     return juce::jlimit(Type(-1), Type(1), wetSignal);
        //          float wetSignal = ((3 * x) / 2) * (1 - (pow(x, 2) / 3));
            //float wetSignal2 = wetSignal;
            float wetSignal = (x * drive * range) / 2;
            float wetSignal2 = std::tanh(wetSignal) / 4;

            /*wetSignal *= drive * range;
            wetSignal2 *= drive * range;*/

            wetSignal = ((wetSignal * blend) + (juce::jlimit(Type(-1), Type(1), wetSignal2) * (1.0f / blend) / 2)) * volume;
            
            //return std::tanh (x);
           // return wetSignal;
            return juce::jlimit(Type(-1), Type(1), wetSignal);
        };

        waveshaper.functionToUse = shaperFunc;

        processorChain.prepare(spec);
    }

    //==============================================================================
    template <typename ProcessContext>
    void process(const ProcessContext& context) noexcept
    {
        processorChain.process(context);
    }

    //==============================================================================
    void reset() noexcept
    {
        processorChain.reset();
    }

    void updateParameters(std::atomic<float>* newDrive, std::atomic<float>* newRange, std::atomic<float>* newBlend, std::atomic<float>* newVolume) {
        drive = *newDrive;
        range = *newRange;
        blend = *newBlend;
        volume = *newVolume;
    }

private:
    //==============================================================================
    enum
    {
        waveshaperIndex,
    };

    using Filter = juce::dsp::IIR::Filter<Type>;
    using FilterCoefs = juce::dsp::IIR::Coefficients<Type>;

    float sampleRate;

    float drive;
    float range;
    float blend;
    float volume;

    juce::dsp::ProcessorChain<
        juce::dsp::WaveShaper<Type, std::function<Type(Type)>>
    > processorChain;
};