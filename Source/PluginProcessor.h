/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AudioEngine.h"

//==============================================================================
/**
*/
class DistortionPedalAudioProcessor  : public juce::AudioProcessor //public juce::AudioProcessorValueTreeState::Listener, public juce::ChangeBroadcaster
{
public:
    //==============================================================================
    DistortionPedalAudioProcessor();
    ~DistortionPedalAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

  //  void parameterChanged(const juce::String& parameter, float newValue) override;


private:
    //==============================================================================
    juce::AudioProcessorValueTreeState parameters;
    AudioEngine audioEngine;


    /*
    std::atomic<float>* driveParameter = nullptr;
    std::atomic<float>* rangeParameter = nullptr;
    std::atomic<float>* blendParameter = nullptr;
    std::atomic<float>* volumeParameter = nullptr;

    std::atomic<float>* roomSizeParameter = nullptr;
    std::atomic<float>* dampingParameter = nullptr;
    std::atomic<float>* wetLevelParameter = nullptr;
    std::atomic<float>* dryLevelParameter = nullptr;
    std::atomic<float>* widthParameter = nullptr;
    std::atomic<float>* freezeModeParameter = nullptr;

    std::atomic<float>* maxDelayTimeParameter = nullptr;
    std::atomic<float>* delayTimeParameter = nullptr;
    std::atomic<float>* wetDelayLevelParameter = nullptr;
    std::atomic<float>* feedbackParameter = nullptr;
    */
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DistortionPedalAudioProcessor)
};
