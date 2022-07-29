/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DistortionPedalAudioProcessorEditor::DistortionPedalAudioProcessorEditor (DistortionPedalAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), audioProcessor (p), valueTreeState(vts), reverbComponent(vts), delayComponent(vts), distortionComponent(vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setLookAndFeel(&customLookAndFeel);
    addAndMakeVisible(distortionComponent);
    addAndMakeVisible(delayComponent);
    addAndMakeVisible(reverbComponent);
    
    setSize(700, 400);

}

DistortionPedalAudioProcessorEditor::~DistortionPedalAudioProcessorEditor()
{

}

//==============================================================================
void DistortionPedalAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colour::fromRGB(0, 0, 0));

    g.setColour(juce::Colours::white);
}

void DistortionPedalAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto area = getLocalBounds();
    auto distortionSize = area.proportionOfWidth(0.29f);
    auto delaySize = area.proportionOfWidth(0.29f);
    auto reverbSize = area.proportionOfWidth(0.42f);

    auto distortionArea = area.removeFromLeft(distortionSize).reduced(5.0f, 5.0f);
    auto delayArea = area.removeFromLeft(delaySize).reduced(5.0f, 5.0f);
    auto reverbArea = area.removeFromLeft(reverbSize).reduced(5.0f, 5.0f);

    distortionComponent.setBounds(distortionArea);
    reverbComponent.setBounds(reverbArea);
    delayComponent.setBounds(delayArea);

}
