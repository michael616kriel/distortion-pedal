/*
  ==============================================================================

    AudioEngine.h
    Created: 23 Jul 2021 1:07:53pm
    Author:  Mike

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "CabSimulator.h"
#include "Distortion.h"
#include "Delay.h"

class AudioEngine : public juce::MPESynthesiser, public juce::AudioProcessorValueTreeState::Listener, public juce::ChangeBroadcaster
{


public:
    static constexpr size_t maxNumVoices = 4;

    //==============================================================================
    AudioEngine(juce::AudioProcessorValueTreeState& vts): parameters(vts)
    {
        parameters.addParameterListener("drive-drive", this);
        parameters.addParameterListener("drive-range", this);
        parameters.addParameterListener("drive-blend", this);
        parameters.addParameterListener("drive-volume", this);

        parameters.addParameterListener("reverb-roomSize", this);
        parameters.addParameterListener("reverb-damping", this);
        parameters.addParameterListener("reverb-wetLevel", this);
        parameters.addParameterListener("reverb-dryLevel", this);
        parameters.addParameterListener("reverb-width", this);
        parameters.addParameterListener("reverb-freezeMode", this);

        parameters.addParameterListener("delay-maxDelayTime", this);
        parameters.addParameterListener("delay-delayTime", this);
        parameters.addParameterListener("delay-wetDelayLevel", this);
        parameters.addParameterListener("delay-feedback", this);

    }

    //==============================================================================
    void prepare(const juce::dsp::ProcessSpec& spec) noexcept
    {
        setCurrentPlaybackSampleRate(spec.sampleRate);
        fxChain.prepare(spec);
    }

    void parameterChanged(const juce::String& parameter, float newValue) override {
        
        if (parameter.startsWith("drive")) {
            auto& distortion = fxChain.template get<distortionIndex>();
            distortion.updateParameters(
                parameters.getRawParameterValue("drive-drive"),
                parameters.getRawParameterValue("drive-range"),
                parameters.getRawParameterValue("drive-blend"),
                parameters.getRawParameterValue("drive-volume"),
                parameters.getRawParameterValue("drive-tone-high"),
                parameters.getRawParameterValue("drive-tone-low")
            ); 
        }
        /*
        if (parameter.startsWith("reverb")) {
            juce::Reverb::Parameters params = juce::Reverb::Parameters();
            params.roomSize = *parameters.getRawParameterValue("reverb-roomSize");
            params.damping = *parameters.getRawParameterValue("reverb-damping");
            params.wetLevel = *parameters.getRawParameterValue("reverb-wetLevel");
            params.dryLevel = *parameters.getRawParameterValue("reverb-dryLevel");
            params.width = *parameters.getRawParameterValue("reverb-width");
            params.freezeMode = *parameters.getRawParameterValue("reverb-freezeMode");
            auto& reverb = fxChain.template get<reverbIndex>();
            reverb.setParameters(params);
        }

        if (parameter.startsWith("delay")) {
            auto& delay = fxChain.template get<delayIndex>();
 
            if (parameter.compare("delay-maxDelayTime")) {
                delay.setMaxDelayTime(*parameters.getRawParameterValue("delay-maxDelayTime"));
            }

            if (parameter.compare("delay-delayTime")) {
                delay.setDelayTime(0, *parameters.getRawParameterValue("delay-delayTime"));
                delay.setDelayTime(1, *parameters.getRawParameterValue("delay-delayTime"));
            }

            if (parameter.compare("delay-wetLevel")) {
                delay.setWetLevel(*parameters.getRawParameterValue("delay-wetLevel"));
            }

            if (parameter.compare("delay-feedback")) {
                delay.setFeedback(*parameters.getRawParameterValue("delay-feedback"));
            }
          
        }
        */
    };

private:

    //==============================================================================
    enum
    {
        distortionIndex,
        cabSimulatorIndex,
       // delayIndex,
       // reverbIndex
    }; 
    juce::AudioProcessorValueTreeState& parameters;
    juce::dsp::ProcessorChain<
        Distortion<float>, 
        CabSimulator<float> 
       // Delay<float>, 
       // juce::dsp::Reverb
    > fxChain;

    //==============================================================================

    void renderNextSubBlock(juce::AudioBuffer<float>& outputAudio, int startSample, int numSamples) override
    {
        MPESynthesiser::renderNextSubBlock(outputAudio, startSample, numSamples);

        auto block = juce::dsp::AudioBlock<float>(outputAudio).getSubBlock((size_t)startSample, (size_t)numSamples);
        auto context = juce::dsp::ProcessContextReplacing<float>(block);
        fxChain.process(context);
    }
};