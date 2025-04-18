#include "Interface/toolTip.hpp"
#include "Interface/UiElement.hpp"

#include "Media/text.hpp"
#include "System/timer.hpp"
#include "System/window.hpp"
#include "Locales/locales.hpp"

#include <vector>
#include <SFML/OpenGL.hpp>


#define WAITING   0
#define FADE_IN   1
#define VISIBLE   2
#define FADE_OUT  3
#define INVISIBLE 4


namespace toolTip 
{
    namespace
	{
        sf::String              currentLocale_;
        std::vector<sf::String> lines_;
        int                     width_(300);
        float                   timer_(-5.f);
        Vector2f                position_;
        short                   state_(INVISIBLE);

        void create()
        {
            sf::String wholeText = currentLocale_;
            sf::String word;
            sf::String line;
            int lastSpace(0);

            lines_.clear();

            if (wholeText.getSize() > 0)
            {
                // search for "\n" and replace them with '\n'
                for (unsigned int i=0; i<wholeText.getSize()-1; ++i)
                    if (wholeText[i] == '\\' && wholeText[i+1] == 'n')
                    {   wholeText[i]  = ' ';
                        wholeText[++i]= '\n';
                    }

                // remove doubled spaces
                for (size_t i=0; i < wholeText.getSize()-1; ++i)
                    if (wholeText[i] == ' ' && wholeText[i+1] == ' ')
                        wholeText.erase(i--, 1);

                // break lines
                for (size_t i=0; i < wholeText.getSize(); ++i)
                {
                    if (wholeText[i] == '\n')
                    {
                        line = "";
                        word = "";
                    }
                    else if (wholeText[i] != ' ')
                    {
                        word += wholeText[i];
                        sf::String tmp(line + word);
                        if (text::getCharacterPos(tmp, tmp.getSize(), 12.f, TEXT_ALIGN_LEFT) > width_)
                        {
                            if (lastSpace == 0)
                            {
                                wholeText.insert(i-1, '\n');
                                line = "";
                                word = wholeText[i];
                                ++i;
                            }else
                            {   wholeText[lastSpace] = '\n';
                                line = word;
                                lastSpace = 0;
                            }
                        }
                    }else
                    {
                        lastSpace = i;
                        line += word + " ";
                        word = "";
                    }
                }

                // create single labels
                line = "";
                int top(0);
                for (size_t i=0; i < wholeText.getSize(); ++i)
                {
                    if (wholeText[i] == '\n')
                    {
                        lines_.push_back(line);
                        line = "";
                    }else
                         line += wholeText[i];
                }
                if (line != "")
                    lines_.push_back(line);
            }
        }

        //  draw
        void drawToolTip(float alpha)
        {
            float scale = UiElement::scale_;
            int height = scale * (lines_.size() * 15 + 10);
            int width = 10;

            for (auto& it : lines_)
            {
                int tmp(text::getCharacterPos(it, it.getSize(), 12.f, TEXT_ALIGN_LEFT) + 10);
                if (tmp > width)
                    width = tmp;
            }
            int mirror(locales::getCurrentLocale().LTR_ ? -1 : 1);
            width *= -mirror * scale;


            const float r(3.f);  // cornerRadius

            //  draw background
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glColor4f(0.0,0.0,0.0, alpha/1.25f);
            glBegin(GL_QUADS);
                glVertex2f(position_.x_, position_.y_ + height + r);
                glVertex2f(position_.x_, position_.y_ - r);
                glVertex2f(position_.x_ + width, position_.y_ - r);
                glVertex2f(position_.x_ + width, position_.y_ + height + r);

                glVertex2f(position_.x_ + width, position_.y_);
                glVertex2f(position_.x_ + width - r*mirror, position_.y_);
                glVertex2f(position_.x_ + width - r*mirror, position_.y_ + height);
                glVertex2f(position_.x_ + width, position_.y_ + height);

                glVertex2f(position_.x_, position_.y_);
                glVertex2f(position_.x_ + r*mirror, position_.y_);
                glVertex2f(position_.x_ + r*mirror, position_.y_ + height);
                glVertex2f(position_.x_, position_.y_ + height);
            glEnd();

            glBegin(GL_TRIANGLE_FAN);
                glVertex2f(position_.x_, position_.y_);

                for (int i = 0; i <= 360; i += 30)
                {
                    if (i == 90)
                    {   glVertex2f(position_.x_, position_.y_ - r);
                        glEnd();
                        glBegin(GL_TRIANGLE_FAN);
                        glVertex2f(position_.x_ + width, position_.y_);
                    }
                    else if (i == 180)
                    {   glVertex2f(position_.x_ + width - r*mirror, position_.y_);
                        glEnd();
                        glBegin(GL_TRIANGLE_FAN);
                        glVertex2f(position_.x_ + width, position_.y_ + height);
                    }
                    else if (i == 270)
                    {   glVertex2f(position_.x_ + width, position_.y_ + height + r);
                        glEnd();
                        glBegin(GL_TRIANGLE_FAN);
                        glVertex2f(position_.x_, position_.y_ + height);
                    }
                    else if (i == 360)
                        glVertex2f(position_.x_ + r*mirror, position_.y_ + height);

                    Vector2f pos;  //  cornerPosition
                    if (i < 90)         pos = position_;
                    else if (i < 180)   pos = position_ + Vector2f(width, 0.f);
                    else if (i < 270)   pos = position_ + Vector2f(width, height);
                    else                pos = position_ + Vector2f(0.f, height);

                    float rad = i*M_PI/180;
                    glVertex2f(pos.x_ + std::cos(rad)*r*mirror,
                               pos.y_ - std::sin(rad)*r);
                }
            glEnd();

            //  draw border
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            glLineWidth(1.f);

            UiElement::setColor4f(0.4,0.8,1.0,alpha);
            glBegin(GL_LINE_LOOP);

                for (int i = 0; i < 360; i += 30)
                {
                    if (i == 0)         glVertex2f(position_.x_ + r*mirror, position_.y_ + height);
                    else if (i == 90)   glVertex2f(position_.x_, position_.y_ - r);
                    else if (i == 180)  glVertex2f(position_.x_ + width - r*mirror, position_.y_);
                    else if (i == 270)  glVertex2f(position_.x_ + width, position_.y_ + height + r);

                    Vector2f pos;  //  cornerPosition
                    if (i < 90)         pos = position_;
                    else if (i < 180)   pos = position_ + Vector2f(width, 0.f);
                    else if (i < 270)   pos = position_ + Vector2f(width, height);
                    else                pos = position_ + Vector2f(0.f, height);

                    float rad = i*M_PI/180;
                    glVertex2f(pos.x_ + std::cos(rad) * r*mirror,
                               pos.y_ - std::sin(rad) * r);
                }
            glEnd();

            //  draw text
            int top = 5;
            for (auto& it : lines_)
            {
                text::drawScreenText(it, position_ + Vector2f(-5 * mirror, top),
                    12.f, TEXT_ALIGN_LEFT, Color3f(0.7f, 0.7f, 0.7f)*alpha);
                top += 15 * scale;
            }
        }
    }

    void draw()
    {
        if (!currentLocale_.isEmpty() && lines_.size() > 0)
        {
            float alpha(0.f);
            float time(timer::realFrameTime()*1.3f);

            switch (state_)
            {
                case WAITING:
                    timer_ += time;
                    if (timer_ > 1.f)
                    {   timer_ = 0.f;
                        state_ = FADE_IN;
                    }
                    break;

                case FADE_IN:
                    timer_ += time*5.f;
                    alpha = timer_;
                    if (timer_ > 1.f)
                        state_ = VISIBLE;
                    break;

                case VISIBLE:
                    alpha = 1.f;
                    break;

                case FADE_OUT:
                    timer_ -= time*5;
                    alpha = timer_;
                    if (timer_ < 0.f)
                        state_ = INVISIBLE;
                    break;
                default:;
            }

            if (settings::bShowToolTips && alpha > 0)
                drawToolTip(alpha);
        }
    }


    void mouseMoved(Vector2f const& position)
    {
        if (state_ == INVISIBLE || state_ == WAITING)
        {
            position_ = position + Vector2f(0, 25);
            state_ = INVISIBLE;
        }
        else if ((position - position_ - Vector2f(0, 25)).lengthSquare() > 60)
        {
            if (state_ != FADE_OUT)
            {   state_ = FADE_OUT;
                timer_ = 1.f;
            }
            if (state_ == WAITING)
                state_ = INVISIBLE;
        }
    }

    void show(const sf::String& text)
    {
        if (text != currentLocale_ && state_ != FADE_OUT)
        {
            currentLocale_ = text;
            if (!currentLocale_.isEmpty())
            {
                create();
                if (state_ == FADE_OUT)
                    state_ = VISIBLE;
            }
        }
        if (!currentLocale_.isEmpty())
        {
            if (state_ == INVISIBLE)
            {   state_ = WAITING;
                timer_ = 0.f;
            }
        }else
            state_ = INVISIBLE;
    }
}
