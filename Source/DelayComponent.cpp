/*
  ==============================================================================

    DelayComponent.cpp
    Created: 25 Jul 2021 6:14:09pm
    Author:  Mike

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DelayComponent.h"

//==============================================================================
DelayComponent::DelayComponent(juce::AudioProcessorValueTreeState& vts) : valueTreeState(vts)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    maxDelayTimeLabel.setText("Max Delay Time", juce::dontSendNotification);
    maxDelayTimeLabel.setFont(juce::Font(12.0f, juce::Font::plain));
    maxDelayTimeLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(maxDelayTimeLabel);

    addAndMakeVisible(maxDelayTimeSlider);
    maxDelayTimeSlider.setSliderStyle(juce::Slider::Rotary);
    maxDelayTimeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    maxDelayTimeAttachment.reset(new SliderAttachment(valueTreeState, "delay-maxDelayTime", maxDelayTimeSlider));

    delayTimeLabel.setText("Delay Time", juce::dontSendNotification);
    delayTimeLabel.setFont(juce::Font(12.0f, juce::Font::plain));
    delayTimeLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(delayTimeLabel);

    addAndMakeVisible(delayTimeSlider);
    delayTimeSlider.setSliderStyle(juce::Slider::Rotary);
    delayTimeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    delayTimeAttachment.reset(new SliderAttachment(valueTreeState, "delay-delayTime", delayTimeSlider));

    wetLevelLabel.setText("Wet Level", juce::dontSendNotification);
    wetLevelLabel.setFont(juce::Font(12.0f, juce::Font::plain));
    wetLevelLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(wetLevelLabel);

    addAndMakeVisible(wetLevelSlider);
    wetLevelSlider.setSliderStyle(juce::Slider::Rotary);
    wetLevelSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    wetLevelAttachment.reset(new SliderAttachment(valueTreeState, "delay-wetLevel", wetLevelSlider));

    feedbackLabel.setText("Feedback", juce::dontSendNotification);
    feedbackLabel.setFont(juce::Font(12.0f, juce::Font::plain));
    feedbackLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(feedbackLabel);

    addAndMakeVisible(feedbackSlider);
    feedbackSlider.setSliderStyle(juce::Slider::Rotary);
    feedbackSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    feedbackAttachment.reset(new SliderAttachment(valueTreeState, "delay-feedback", feedbackSlider));

}

DelayComponent::~DelayComponent()
{

}

void DelayComponent::paint(juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll(juce::Colours::black);   // clear the background

    g.setColour(juce::Colours::grey);
    g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

}

void DelayComponent::resized()
{
    auto labelHeight = 10.0f;
    auto area = getLocalBounds().reduced(5.0f, 5.0f);
    auto width = area.getWidth() / 4;

    auto maxDelayTimeArea = area.removeFromLeft(width);
    maxDelayTimeSlider.setBounds(maxDelayTimeArea.removeFromTop(maxDelayTimeArea.getHeight() - labelHeight));
    maxDelayTimeLabel.setBounds(maxDelayTimeArea.removeFromBottom(labelHeight));

    auto delayTimeArea = area.removeFromLeft(width);
    delayTimeSlider.setBounds(delayTimeArea.removeFromTop(delayTimeArea.getHeight() - labelHeight));
    delayTimeLabel.setBounds(delayTimeArea.removeFromBottom(labelHeight));

    auto wetLevelArea = area.removeFromLeft(width);
    wetLevelSlider.setBounds(wetLevelArea.removeFromTop(wetLevelArea.getHeight() - labelHeight));
    wetLevelLabel.setBounds(wetLevelArea.removeFromBottom(labelHeight));

    auto feedbackArea = area.removeFromLeft(width);
    feedbackSlider.setBounds(feedbackArea.removeFromTop(feedbackArea.getHeight() - labelHeight));
    feedbackLabel.setBounds(feedbackArea.removeFromBottom(labelHeight));

}
