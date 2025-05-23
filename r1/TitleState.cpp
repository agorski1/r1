#include "TitleState.h"
#include "Utility.h"


TitleState::TitleState(StateStack& stack, Context context)
    : State(stack, context)
    , mText()
    , mShowText(true)
    , mTextEffectTime(sf::Time::Zero)
{
    mBackgroundSprite.setTexture(context.textures->get(Textures::TitleScreen));

    mText.setFont(context.fonts->get(Fonts::Main));
    mText.setString("Press any key to start");
    centerOrigin(mText);
    mText.setPosition(context.window->getView().getSize() / 2.f);
}

void TitleState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.draw(mBackgroundSprite);
    if (mShowText)
        window.draw(mText);
}

bool TitleState::update(sf::Time dt)
{
    mTextEffectTime += dt;

    if (mTextEffectTime >= sf::seconds(0.5f))
    {
        mShowText = !mShowText;
        mTextEffectTime = sf::seconds(0.f);
    }

    return true;
}

bool TitleState::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        requestStackPop();
        requestStackPush(States::Menu);

        return false;
    }

    return true;
}
