#include "Interface/ColorPickerWindow.hpp"

#include "Interface/ColorPicker.hpp"
#include "Interface/Button.hpp"
#include "Locales/locales.hpp"
#include "Menu/menus.hpp"
#include "Media/texture.hpp"
#include "System/window.hpp"

#include <SFML/OpenGL.hpp>


ColorPickerWindow::ColorPickerWindow (ColorPicker* parent, Color3f* color)
    :UiWindow(190, 185)
    ,parent_(parent)
    ,color_(color)
    ,Ok_(new Button(locales::getLocale(locales::Ok), "", &kOk_, Vector2f(110, 155), 70, 20))
    ,kOk_(false)
{
    addWidget(Ok_);
}

void ColorPickerWindow::draw() const
{
    UiWindow::draw();

    Vector2f viewPort = window::getViewPort();
    Vector2f origin;

    origin.x_ = topLeft_.x_ + (viewPort.x_ - width_)/2;
    origin.y_ = topLeft_.y_ + (viewPort.y_ - height_)/2;

    // update color according to mouse
    Vector2f mouse = window::PixelToCoord(window::getMousePosition());
    int x(mouse.x_), y(mouse.y_);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
        x > origin.x_ && x < origin.x_ + 190 * scale_ &&
        y > origin.y_ && y < origin.y_ + 150 * scale_)
    {
        float max = 119.9f * scale_;
        if (x > origin.x_ + 140 * scale_)
        {
            float offset(y - origin.y_ - 10.f);
            if (offset > max)  offset = max;
            if (offset < 0)    offset = 0;
            color_->h(offset * 3.f / scale_);  // hue
        }else
        {
            float offsetY(y - origin.y_ - 10.f);
            float offsetX(x - origin.x_ - 10.f);
            if (offsetY > max)  offsetY = max;
            if (offsetY < 0)    offsetY = 0;
            if (offsetX > max)  offsetX = max;
            if (offsetX < 0)    offsetX = 0;
            color_->s(1.f    - offsetY / (120.f * scale_));  // sat
            color_->v(0.001f + offsetX / (120.f * scale_));  // val
        }
    }

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // draw b&w background grade
    glBegin(GL_QUADS);
        setColor3f(0.f, 0.f, 0.f);
        glVertex2f(origin.x_ + 10.f, origin.y_ + 10.f);
        glVertex2f(origin.x_ + 10.f, origin.y_ + 130.f * scale_);
        setColor3f(1.f, 1.f, 1.f);
        glVertex2f(origin.x_ + 130.f * scale_, origin.y_ + 130.f * scale_);
        glVertex2f(origin.x_ + 130.f * scale_, origin.y_ + 10.f);
    glEnd();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture::getTexture(texture::Interface));

    // draw hue stripe
    setColor3f(1.f, 1.f, 1.f);
    glBegin(GL_QUADS);
        glTexCoord2f(0.234375f, 0.390625f);   glVertex2f(origin.x_ + 150.f * scale_, origin.y_ + 10.f);
        glTexCoord2f(0.234375f, 0.625f);      glVertex2f(origin.x_ + 150.f * scale_, origin.y_ + 130.f * scale_);
        glTexCoord2f(0.29296875f, 0.625f);    glVertex2f(origin.x_ + 180.f * scale_, origin.y_ + 130.f * scale_);
        glTexCoord2f(0.29296875f, 0.390625f); glVertex2f(origin.x_ + 180.f * scale_, origin.y_ + 10.f);
    glEnd();

    // draw colored edge
    Color3f tmp(*color_);
    tmp.s(1.f);
    tmp.v(1.f);
    tmp.gl3f();
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0.390625f);          glVertex2f(origin.x_ + 10.f, origin.y_ + 10.f);
        glTexCoord2f(0, 0.625f);             glVertex2f(origin.x_ + 10.f, origin.y_ + 130.f * scale_);
        glTexCoord2f(0.234375f, 0.625f);     glVertex2f(origin.x_ + 130.f * scale_, origin.y_ + 130.f * scale_);
        glTexCoord2f(0.234375f, 0.390625f);  glVertex2f(origin.x_ + 130.f * scale_, origin.y_ + 10.f);
    glEnd();

    // draw color selector
    float hue = color_->h();
    float sat = color_->s();
    float val = color_->v();

    tmp = *color_;
    tmp.s(1.f - sat);
    tmp.v(1.f - val);
    tmp.gl3f();
    Vector2f pickerLocation(origin + Vector2f(10.f + val*120.f * scale_, 130.f * scale_ - sat * 120.f * scale_));
    glBegin(GL_QUADS);
        glTexCoord2f(0.8359375f, 0.06640625f);  glVertex2f(pickerLocation.x_+8.f, pickerLocation.y_+8.f);
        glTexCoord2f(0.8359375f, 0.09765625f);  glVertex2f(pickerLocation.x_+8.f, pickerLocation.y_-8.f);
        glTexCoord2f(0.8671875f, 0.09765625f);  glVertex2f(pickerLocation.x_-8.f, pickerLocation.y_-8.f);
        glTexCoord2f(0.8671875f, 0.06640625f);  glVertex2f(pickerLocation.x_-8.f, pickerLocation.y_+8.f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    // draw hue selector
    setColor3f(1.f, 1.f, 1.f);
    glLineWidth(2.f);
    glBegin(GL_LINES);
        glVertex2f(origin.x_ + 148.f * scale_, origin.y_ + hue/3.f * scale_ +10.f);
        glVertex2f(origin.x_ + 182.f * scale_, origin.y_ + hue/3.f * scale_ +10.f);
    glEnd();
}

void ColorPickerWindow::checkWidgets()
{
    if (kOk_)
    {   kOk_ = false;
        menus::hideWindow();
    }
}
