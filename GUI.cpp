#include "GUI.h"
#include <string>

void GUI::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(text);
}

GUI::GUI() {
    font.loadFromFile("OpenSans-Light.ttf");
    text.setFont(font);
    text.setCharacterSize(24);
}

void GUI::setParameters(Parameters param) {
    text.setString("Definition : " + std::to_string(param.definition.x) + " x " + std::to_string(param.definition.y)
                   + "\nIterations : " + std::to_string(param.iterMax)
                   + "\nX : " + std::to_string(param.center.x) + "\nY : " + std::to_string(param.center.y)
    );

}
