/*
  ==============================================================================

    CabSimulator.h
    Created: 23 Jul 2021 1:05:21pm
    Author:  Mike

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

template <typename Type>
class CabSimulator
{
public:
    //==============================================================================
    CabSimulator()
    {
        auto dir = juce::File::getCurrentWorkingDirectory();

        int numTries = 0;

        while (!dir.getChildFile("Resources").exists() && numTries++ < 15)
            dir = dir.getParentDirectory();

        auto& convolution = processorChain.template get<convolutionIndex>();

        convolution.loadImpulseResponse(dir.getChildFile("Resources").getChildFile("GuitarHack JJ CENTRE 0.wav"),
            juce::dsp::Convolution::Stereo::yes,
            juce::dsp::Convolution::Trim::no,
            1024);
    }
     
    //==============================================================================
    void prepare(const juce::dsp::ProcessSpec& spec)
    {
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

private:
    //==============================================================================
    enum
    {
        convolutionIndex
    };

    juce::dsp::ProcessorChain<juce::dsp::Convolution> processorChain;
};
