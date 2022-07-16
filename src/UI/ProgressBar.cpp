#include "UI/ProgressBar.hpp"

using namespace UI;


ProgressBar::ProgressBar(const sf::Vector2f& size) : _bar(size), _originalSize(size) {
    _bar.setFillColor(_primaryColor);
}

void ProgressBar::setProgress(const float amount) {
    _progress = amount;
    if (_progress > 1.0f)
        _progress = 1.0f;
    else if (_progress < 0.0f)
        _progress = 0.0f;
    updateBar();
}

float ProgressBar::getProgress() const {
    return _progress;
}

void ProgressBar::addToProgress(const float amount) {
    _progress += amount;
    if (_progress > 1.0f)
        _progress = 1.0f;
    else if (_progress < 0.0f)
        _progress = 0.0f;
    updateBar();
}

void ProgressBar::setPrimaryColor(const sf::Color color) {
    _primaryColor = color;
    updateBar();
}

void ProgressBar::setSecondaryColor(const sf::Color color) {
    _secondaryColor = color;
    updateBar();
}

void ProgressBar::setSize(const sf::Vector2f &size) {
    _originalSize = size;
    updateBar();
}

void ProgressBar::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(_bar, states);
}

void ProgressBar::updateBar() {
    _bar.setSize({ _originalSize.x * _progress, _originalSize.y });
    if (_progress > 0.2f)
        _bar.setFillColor(_primaryColor);
    else
        _bar.setFillColor(_secondaryColor);
}
