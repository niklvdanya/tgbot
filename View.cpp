#include "View.h"
#include "BotView.h"

std::shared_ptr<IBotView> createView(TgBot::Bot& bot)
{
    return std::make_shared<BotView>(bot);
}